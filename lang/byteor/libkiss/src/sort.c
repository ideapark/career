/*
 * Copyright (c) 2014 - 2015, Zhou Peng <p@ctriple.cn>
 *        ALL RIGHTS RESERVED
 */

#include "../include/kiss.h"

static inline void swap(char *str, int i, int j)
{
	char temp;

	temp = str[i];
	str[i] = str[j];
	str[j] = temp;
}

static int partition(char *str, int lo, int hi)
{
	int i, pivot_idx, store_idx;
	char pivot_val;

	pivot_idx = lo;
	pivot_val = str[pivot_idx];

	swap(str, pivot_idx, hi);
	store_idx = lo;

	for (i = lo; i < hi; i++) {
		if (str[i] < pivot_val) {
			swap(str, store_idx, i);
			store_idx++;
		}
	}

	swap(str, store_idx, hi);

	return store_idx;
}

static void quicksort(char *str, int lo, int hi)
{
	int mid;

	if (lo < hi) {
		mid = partition(str, lo, hi);
		quicksort(str, lo, mid-1);
		quicksort(str, mid+1, hi);
	}
}

void sort(char *str)
{
	int lo, hi;

	lo = hi = 0;

	while (str[hi+1] != '\0')
		hi++;

	quicksort(str, lo, hi);
}
