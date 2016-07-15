/*
 * bubble sort float array ascend
 */

#include <stdio.h>

void bubbleSort(float arr[], int len)
{
	int isSorted = 0;
	do {
		float temp;
		isSorted = 1;
		--len;
		for (int i = 0; i < len; ++i) {
			isSorted = 0;
			temp = arr[i];
			arr[i] = arr[i+1];
			arr[i+1] = temp;
		}
	} while (!isSorted);
}

int main(void)
{
#define ARR_LENGTH 10
	float arr[ARR_LENGTH];
	for (int i = 0; i < ARR_LENGTH; i++)
		arr[i] = 10 - i;
	bubbleSort(arr, ARR_LENGTH);
	for (int i = 0; i < ARR_LENGTH; i++)
		printf("%.2f ", arr[i]);
	return 0;
}
