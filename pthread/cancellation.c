/*
 * This program does a heuristic search for an integer, then cancels
 * all threads that didn't find it. The actual heuristic is silly
 * (it calls rand_r()), but the technique is valid.
 *
 * All of the calls to delay() are there to slow things down and
 * make different contention situations more likely.
 *
 * A couple of simple cleanup handlers are included. In a real program,
 * these should be even more complex.
 *
 * NB: sem_trywait() -> EBUSY in Solaris 2.5 is a bug.
 * It *should* be EAGAIN (fixed in 2.6).
 */

#define _POSIX_C_SOURCE  199506L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>

#ifdef __sun              /* This is a bug in Solaris 2.5 */
#define MY_EAGAIN EBUSY
#else
#define MY_EAGAIN EAGAIN  /* Correct errno value from trywait() */
#endif

#define NUM_THREADS 25  /* the number of searching threads */

pthread_attr_t  attr;
pthread_t       threads[NUM_THREADS];
pthread_mutex_t threads_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t wait_lock    = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t rand_lock    = PTHREAD_MUTEX_INITIALIZER;
sem_t           death_lock;  /* I'm using it like a lock */
pthread_mutex_t count_lock   = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  wait_cv      = PTHREAD_COND_INITIALIZER;

int answer;  /* Protected by death_lock */

/*
 * Note the encapsulation
 */
void count_tries(int i)
{
    static int count = 0, old_count = 0, max_count = 0;
    static pthread_mutex_t count_lock = PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_lock(&count_lock);
    count += i;
    if (i == -1)
        printf("Total attempt count: %d\n", max_count);
    if (count > max_count)
        max_count = count;
    pthread_mutex_unlock(&count_lock);
}

void cleanup_count(void *arg)
{
    int *ip = (int *)arg;
    int i = *ip;
    pthread_t tid = pthread_self();
    char *name = thread_name(tid);

    count_tries(i);
    printf("%s exited (maybe cancelled) on its %d try.\n", name, i);
    /* Note that you can't tell if the thread exited, or was cancelled */
}

void cleanup_lock(void *arg)
{
    pthread_t tid = pthread_self();
    char *name = thread_name(tid);

    printf("Freeing & releasing: %s\n", name);
    free(arg);
    pthread_mutex_unlock(&rand_lock);
}

void *search(void *arg)
{
    char *p;
    unsigned int seed;
    int i = 0, j, err, guess, target = (int)arg;
    pthread_t tid = pthread_self();
    char *name = thread_name(tid);
    seed = (unsigned int)tid;

    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_cleanup_push(cleanup_count, (void *)&i);  /* Q: Why &i ? */

    while (1) {
        i++;

        /* Extra stuff to make it more realistic and complex */
        pthread_mutex_lock(&rand_lock);
        p = (char *)malloc(10);  /* Must free this up! */
        /* Q: What if you allow cancellation here? */
        pthread_cleanup_push(cleanup_lock, (void *)p);
        guess = rand_r(&seed);
        delay(0, 10);
        pthread_testcancel();
        pthread_cleanup_pop(0);
        /* Q: What if you allow cancellation here? */
        free(p);
        pthread_mutex_unlock(&rand_lock);

        delay(0, 10);

        if (target == guess) {
            printf("%s found the number on try %d!\n", name, i);
            /* I could also simply do sem_wait() & let cancellation work */
            while (((err = sem_trywait(&death_lock)) == -1) && (errno == EINTR))
                ;
            if ((err == -1) && (errno == MY_EAGAIN)) {
                printf("%s Exiting...\n", name);
                pthread_exit(NULL);
            }
            count_tries(i);
            answer = guess;
            delay(5000, 0);  /* Encourage a few more threads to find it */
            pthread_mutex_lock(&threads_lock);
            for (j = 0; j < NUM_THREADS; j++)
                if (!pthread_equal(threads[j], tid))
                    if (pthread_cancel(threads[j]) == ESRCH)
                        printf("Missed thread %s\n", thread_name(threads[j]));
            pthread_mutex_unlock(&threads_lock);
            break; /* Cannot release death_lock yet! */
        }
        pthread_testcancel();  /* Insert a known cancellation point */
    }
    pthread_cleanup_pop(1);
    pthread_exit(NULL);
}

void start_searches()
{
    int i, pid, n_cancelled = 0, status;
    pthread_t tid;

    pid = getpid();

    while (pid > RAND_MAX)
        pid /= 2;

    printf("\n\nSearching for the number = %d...\n", pid);

    pthread_mutex_lock(&threads_lock);

    /* Q: Why do we need threads_lock? */
    for (i = 0; i < NUM_THREADS; i++)
        pthread_create(&threads[i], &attr, search, (void *)pid);
    pthread_mutex_unlock(&threads_lock);

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_mutex_lock(&threads_lock);
        tid = threads[i];  /* Acutally a constant now */
        pthread_mutex_unlock(&threads_lock);  /* Q: Why like this? */
        pthread_join(tid, (void **)&status);
        if ((void *)status == (void *)PTHREAD_CANCELED)
            n_cancelled++;
    }
    sem_post(&death_lock);
    count_tries(-1);
    printf("%d of the threads were cancelled.\n", n_cancelled);
    printf("The answer was: %d\n", answer);
}

int main(void)
{
    int i;

    pthread_attr_init(&attr);
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    sem_init(&death_lock, NULL, 1);

    for (i = 0; i < 2; i++)
        start_searches();

    pthread_exit(NULL);
}
