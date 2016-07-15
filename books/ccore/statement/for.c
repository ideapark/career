#include <stdio.h>

int main(void)
{
#define ARR_LENGTH 1000
	long arr[ARR_LENGTH];
	int i;
	for (i = 0; i < ARR_LENGTH; ++i)
		arr[i] = 2 * i;
	for (i = 0; i < ARR_LENGTH; ++i) {
		if (i % 10 == 0)
			printf("%s", "\n");
		printf("%6ld ", arr[i]);
	}
	return 0;
}
