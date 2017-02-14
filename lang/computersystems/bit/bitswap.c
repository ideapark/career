#include <stdio.h>

void inplace_swap(int *x, int *y)
{
	*y = *x ^ *y;
	*x = *x ^ *y;
	*y = *x ^ *y;
}

int main(void)
{
	int x = 11;
	int y = 22;

	printf("before: x = %d, y = %d\n", x, y);
	inplace_swap(&x, &y);
	printf(" after: x = %d, y = %d\n", x, y);

	return 0;
}
