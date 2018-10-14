/*
 * DATA PADDING:
 *
 * 2^n bytes data type, its address's last n bits must be 0.
 */

#include <stdio.h>

int main(void)
{
	char wolf[] = "like a wolf";
	char *p = &wolf[1];
	unsigned long l = *(unsigned long *)p;

	printf("long value cast from char: %ld\n", l);

	return 0;
}
