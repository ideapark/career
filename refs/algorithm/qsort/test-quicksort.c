/*
 * Quick Sorting Tests
 *
 * Copyright (C) Zhou Peng <p@ctriple.cn>
 */

#include <assert.h>

#define LEN(arr)  (sizeof(arr)/sizeof(arr[0]))

int main(void)
{
	int origin1[] = { 10, 9, 8, 7, 6, 1, 2, 3, 4, 5 };
	int expect1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	quicksort(origin1, LEN(origin1));
	for (int i = 0; i < LEN(origin1); i++)
		assert(origin1[i] == expect1[i]);

	int origin2[] = { 'a', 'b', 'c', 'd', 'e', 'A', 'B', 'C', 'D', 'E' };
	int expect2[] = { 'A', 'B', 'C', 'D', 'E', 'a', 'b', 'c', 'd', 'e' };

	quicksort(origin2, LEN(origin2));
	for (int i = 0; i < LEN(origin2); i++)
		assert(origin2[i] == expect2[i]);

	return 0;
}
