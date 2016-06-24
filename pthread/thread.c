#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS  10

void *ThreadFunc(void *threadId)
{
	long tid;

	tid = (long)threadId;
	sleep(random() % NUM_THREADS);
	printf("It's me, thread #%ld\n", tid);
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	pthread_t threads[NUM_THREADS];
	int rc;
	long t;

	for (t = 0; t < NUM_THREADS; t++) {
		printf("Creating thread #%ld\n", t);
		rc = pthread_create(&threads[t], NULL, ThreadFunc, (void *)t);
		if (rc) {
			printf("ERROR: return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}

	for (t = 0; t < NUM_THREADS; t++) {
		pthread_join(threads[t], NULL);
	}

	printf("Done.\n");

	pthread_exit(NULL);
}
