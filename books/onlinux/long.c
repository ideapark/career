#include <stdio.h>

int main(void)
{
	printf("C standard ensure sizeof(long) equals to arch word length: %ld\n",
			sizeof(long));

	return 0;
}
