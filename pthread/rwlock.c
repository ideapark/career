#include <pthread.h>

int shared;
pthread_rwlock_t lock;

void *thread_function(void *arg)
{
	pthread_rwlock_rdlock(&lock);
	/* Read from the shared resource */
	pthread_rwlock_unlock(&lock);
	return NULL;
}

int main(void)
{
	pthread_rwlock_init(&lock, NULL);

	/* Start threads here */

	pthread_rwlock_wrlock(&lock);
	/* Write to the shared resource */
	pthread_rwlock_unlock(&lock);

	/* Join with threads here */

	pthread_rwlock_destroy(&lock);
	return 0;
}
