#include <semaphore.h>

int shared;
sem_t binary_sem;  /* Used like a mutex */

void *thread_function(void *arg)
{
	sem_wait(&binary_sem);  /* Decrements count */
	/* Use shared resource */
	sem_signal(&binary_sem);  /* Increments count */
}

void main(void)
{
	sem_init(&binary_sem, 1);  /* Give semaphore initial count */

	/* Start threas here */

	sem_wait(&binary_sem);
	/* Use shared resource */
	sem_signal(&binary_sem);

	/* Join with threads here */

	sem_destroy(&binary_sem);
	return 0;
}
