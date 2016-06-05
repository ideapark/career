#include <pthread.h>
#include <unistd.h>

pthread_cond_t is_zero;
pthread_mutex_t mutex; /* Condition variables needs a mutex */
int shared_data = 32767;  /* Or some other large number */

void *thread_function(void *arg)
{
    /* Imagine doing something useful */
    while (shared_data > 0) {
        /* The other thread sees the shared data consistently */
        pthread_mutex_lock(&mutex);
        --shared_data;
        pthread_mutex_unlock(&mutex);
    }

    /* Signal the condition */
    pthread_cond_signal(&is_zero);
    return NULL;
}

int main(void)
{
    pthread_t thread_ID;
    void *exit_status;

    pthread_cond_init(&is_zero, NULL);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&thread_ID, NULL, thread_function, NULL);

    /* Wait for the shared data to reach zero */
    pthread_mutex_lock(&mutex);
    while (shared_data != 0)
        pthread_cond_wait(&is_zero, &mutex);
    pthread_mutex_unlock(&mutex);

    pthread_join(thread_ID, &exit_status);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&is_zero);
    return 0;
}
