#include <stdio.h>

/* WARNNING: This is buggy code */
float sum_elements(float a[], unsigned length)
{
	int i;
	float result = 0;

	for (i = 0; i <= length-1; i++) {
		result += a[i];
	}

	return result;
}

int main(void)
{
	float a[5];

	sum_elements(a, 5);
	sum_elements(NULL, 0); /* Fetal: null pointer exception */

	return 0;
}
