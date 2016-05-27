#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/* STATE_A Thread A runs next, STATE_B = Thread B runs next */
enum {STATE_A, STATE_B} state = STATE_A;

pthread_cond_t  condA = PTHREAD_COND_INITIALIZER;
pthread_cond_t  condB = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *threadA()
{
    int i = 0, loopNum;

    while (i < 3) {
        /* Wait for state A*/
        pthread_mutex_lock(&mutex);

        while (state != STATE_A)
            pthread_cond_wait(&condA, &mutex);
        pthread_mutex_unlock(&mutex);

        /* do stuff */
        for (loopNum = 0; loopNum < 2; loopNum++)
            printf("A: Hello %d\n", loopNum);

        /* Set state to B and wake up thread B */
        pthread_mutex_lock(&mutex);
        state = STATE_B;
        pthread_cond_signal(&condB);
        pthread_mutex_unlock(&mutex);

        i++;
    }

    return NULL;
}

void *threadB()
{
    int n = 0;

    while (n < 3) {
        /* Wait for state B */
        pthread_mutex_lock(&mutex);
        while (state != STATE_B)
            pthread_cond_wait(&condB, &mutex);
        pthread_mutex_unlock(&mutex);

        /* do stuff */
        printf("B: Goodbye\n");

        /* Set state to A and wake up thread A */
        pthread_mutex_lock(&mutex);
        state = STATE_A;
        pthread_cond_signal(&condA);
        pthread_mutex_unlock(&mutex);

        n++;
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t a, b;

    pthread_create(&a, NULL, threadA, NULL);
    pthread_create(&b, NULL, threadB, NULL);

    pthread_join(a, NULL);
    pthread_join(b, NULL);

    return 0;
}
