#include <stdio.h>
#include <unistd.h>
#include <sys/times.h>
#include <sys/types.h>
#include <time.h>

#define SIZE_MIN  (1024)
#define SIZE_MAX  (32*1024*1024)
#define STRIDE_MIN  2
#define STRIDE_MAX  108

int array[SIZE_MAX];

/*
 * Returns CPU time in seconds.
 */
double get_seconds()
{
	struct timespec ts;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
	return ts.tv_sec + ts.tv_nsec / 1e9;
}

/*
 * Measures CPU time per read+write and prints results.
 * @size: array size
 * @stride: stride length of the access pattern
 */
void benchmark(long size, int stride)
{
	long limit;
	int index, temp;
	int iters, iters2;
	double sec0, sec;

	sec = 0;
	limit = size - stride + 1;

	iters = 0;
	do {
		sec0 = get_seconds();

		for (index = 0; index < limit; index += stride)
			array[index] = array[index] + 1;

		iters = iters + 1;
		sec = sec + (get_seconds() - sec0);
	} while (sec < 0.1);  /* run at least 0.1 seconds */

	iters2 = 0;
	do {
		sec0 = get_seconds();

		for (index = 0; index < limit; index += stride)
			temp = temp + index;

		iters2 = iters2 + 1;
		sec = sec - (get_seconds() - sec0);
	} while (iters2 < iters);

	printf("Size: %7ld Stride: %7ld read+write: %4.4lf ns\n",
	       size * sizeof(int),
	       stride * sizeof(int),
	       sec * 1e9 / iters / limit * stride);
}

int main(void)
{
	long size;
	int stride;

	for (size = SIZE_MIN; size <= SIZE_MAX; size = size * 2)
		for (stride = STRIDE_MIN; stride <= STRIDE_MAX; stride = stride * 2)
			benchmark(size, stride);

	return 0;
}
