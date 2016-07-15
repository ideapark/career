#include <time.h>
#include <stdio.h>

int main(void)
{
	time_t now;
	time(&now); /* get now time(from 1/1/70) */
	printf("Date: %.24s GMT\n", asctime(gmtime(&now)));
	return 0;
}
