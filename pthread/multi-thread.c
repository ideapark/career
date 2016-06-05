/*
 * Simple program that just illustrates thread creation,
 * thread exiting, waiting for threads, and returning
 * status from threads.
 */

#define _POSIX_C_SOURCE  199506L

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

/* Function prototypes for thread routines */
void *sub_a(void *arg);
void *sub_b(void *arg);
void *sub_c(void *arg);
void *sub_d(void *arg);
void *sub_e(void *arg);

pthread_t thr_a;
pthread_t thr_b;
pthread_t thr_c;
pthread_t thr_d;
pthread_t thr_e;
pthread_t thr_main;

pthread_attr_t attr;

int zero;

int timediff()
{
    return (time(NULL)-zero);
}

/* FIXME: NOT thread safe */
char *thread_name(pthread_t tid)
{
    static char namebuf[64];
    sprintf(namebuf, "thread-%ld", tid);
    return namebuf;
}

void *sub_a(void *arg)
{
    pthread_t tid = pthread_self();
    printf("[%2d] A: \t In thread A [%s]\n", timediff(), thread_name(tid));

    sleep(1);
    pthread_create(&thr_d, &attr, sub_d, NULL);
    printf("[%2d] A: \t Created thread D [%s]\n", timediff(), thread_name(thr_d));

    sleep(3);
    printf("[%2d] A: \t Thread exiting...\n", timediff());
    return ((void *)77);  /* Same as pthread_exit((void *)77) */
}

void *sub_b(void *arg)
{
    pthread_t tid = pthread_self();
    printf("[%2d] B: \t In thread B [%s]\n", timediff(), thread_name(tid));

    sleep(4);
    printf("[%2d] B: \t Thread exiting...\n", timediff());
    pthread_exit(NULL);
}

void *sub_c(void *arg)
{
    void *status;
    int err;
    pthread_t tid = pthread_self();
    char *name = thread_name(tid);

    printf("[%2d] C: \t In thread C [%s]\n", timediff(), name);
    sleep(2);

    printf("[%2d] C: \t Joining main thread...\n", timediff());
    if ((err = pthread_join(thr_main, &status))) {
        printf("pthread_join Error. %s", strerror(err));
        exit(1);
    }
    printf("[%2d] C: \t Main thread [%s] returning status: %d\n", timediff(), thread_name(thr_main), (int)status);

    sleep(1);
    pthread_create(&thr_b, &attr, sub_b, NULL);
    printf("[%2d] C: \t Created thread B [%s]\n", timediff(), thread_name(thr_b));

    sleep(4);
    printf("[%2d] C: \t Thread exiting...\n", timediff());
    pthread_exit((void *)88);
}

void *cleanup(void *arg)
{
    pthread_t tid = pthread_self();
    char *name = thread_name(tid);

    printf("[%2d] D: \t %s cancelled! \n", timediff(), name);
    return NULL;
}

void *sub_d(void *arg)
{
    pthread_t thr_e;
    pthread_t tid = pthread_self();

    printf("[%2d] D: \t In thread D [%s]\n", timediff(), thread_name(tid));

    pthread_cleanup_push(cleanup, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

    sleep(1);
    pthread_create(&thr_e, &attr, sub_e, NULL);
    printf("[%2d] D: \t Created thread E [%s]\n", timediff(), thread_name(thr_e));

    sleep(5);
    /* D should get cancelled before this runs */
    printf("[%2d] D: \t Thread exiting...\n", timediff());
    pthread_cleanup_pop(0);
    return ((void *)55);
}

void *sub_e(void *arg)
{
    int err;
    void *status;
    pthread_t tid = pthread_self();

    printf("[%2d] E: \t In thread E [%s]\n", timediff(), thread_name(tid));

    sleep(3);
    printf("[%2d] E: \t Joining thread A...\n", timediff());
    if ((err = pthread_join(thr_a, &status))) {
        printf("pthread_join Error. %s", strerror(err));
        exit(1);
    }
    printf("[%2d] E: \t Thread A [%s] returning status: %d\n", timediff(), thread_name(thr_a), (int)status);

    sleep(2);

    printf("[%2d] E: \t Joining thread C...\n", timediff());
    if ((err = pthread_join(thr_c, &status))) {
        printf("pthread_join Error. %s", strerror(err));
        exit(1);
    }
    printf("[%2d] E: \t Thread C [%s] returning status: %d\n", timediff(), thread_name(thr_c), (int)status);

    sleep(2);
    printf("[%2d] E: \t Joining thread D...\n", timediff());
    if ((err = pthread_join(thr_d, &status))) {
        printf("pthread_join Error. %s", strerror(err));
        exit(1);
    }
    if ((void *)status == (void *)PTHREAD_CANCELED)
        printf("[%2d] E: \t Thread D [%s] returning status: PTHREAD_CANCELED", timediff(), thread_name(thr_c));
    else
        printf("[%2d] E: \t Thread D [%s] returning status: %d\n", timediff(), thread_name(thr_c), (int)status);

    sleep(1);
    printf("[%2d] E: Thread exiting...\n", timediff());
    pthread_exit((void *)44);
}

int main(void)
{
    zero = time(NULL);
    thr_main = pthread_self();
    printf("Time Thread \t Event\n");
    printf("==== ====== \t =====\n");
    printf("[%2d] Main: \t Started [%s]\n", timediff(), thread_name(thr_main));

    pthread_attr_init(&attr);
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    sleep(1);
    pthread_create(&thr_a, &attr, sub_a, NULL);
    printf("[%2d] Main: \t Created thread A [%s]\n", timediff(), thread_name(thr_a));

    sleep(1);
    pthread_create(&thr_c, &attr, sub_c, NULL);
    printf("[%2d] Main: \t Created thread C [%s]\n", timediff(), thread_name(thr_c));

    sleep(2);
    printf("[%2d] Main: \t Cancelling thread D [%s]\n", timediff(), thread_name(thr_c));
    pthread_cancel(thr_d);

    sleep(1);
    printf("[%2d] Main: \t Thread exiting...\n", timediff());
    pthread_exit((void *)NULL);
}
