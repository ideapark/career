#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

pthread_mutex_t lock;
static int shared_data;

void *thread_function(void *arg)
{
	int i;
	for (i = 0; i < 1024*1024; ++i) {
		/* Access the shared data here */
		pthread_mutex_lock(&lock);
		shared_data += i;
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}

int main(void)
{
	pthread_t thread_ID;
	void *exit_status;
	int i;

	/* Initialize the mutex before trying to use it */
	pthread_mutex_init(&lock, NULL);
	pthread_create(&thread_ID, NULL, thread_function, NULL);

	/* Try to use the shared data */
	for (i = 0; i < 10; ++i) {
		pthread_mutex_lock(&lock);
		printf("\rShared integer's value = %d\n", shared_data);
		pthread_mutex_unlock(&lock);
	}
	printf("\n");

	pthread_join(thread_ID, &exit_status);

	/* Clean up the mutex when we are finished with it */
	pthread_mutex_destroy(&lock);
	return 0;
}
