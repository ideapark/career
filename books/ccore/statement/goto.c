/*
 * Handle function inner error
 */

#include <stdbool.h> // bool, true, false (C99)
#include <stdio.h>

#define MAX_ARR_LENGTH 10

bool calculate(double arr[], int len, double *result)
{
	bool error = false;
	if (len < 1 || len > MAX_ARR_LENGTH)
		goto error_exit;
	for (int i = 0; i < len; ++i) {
		if (error)
			goto error_exit;
	}
	return true;

error_exit:
	printf("goto error and exit!\n");
	*result = 0.0;
	return false;
}

int main(void)
{
	double arr[MAX_ARR_LENGTH] = {
		1, 2, 3, 4, 5,
		6, 7, 8, 9, 10
	};
	double result = 0.0;
	calculate(arr, MAX_ARR_LENGTH, &result);
	calculate(arr, MAX_ARR_LENGTH+1, &result);
	calculate(arr, -1, &result);
	return 0;
}
