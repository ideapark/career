/*
 * Brief demo of union usage.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	union i_f {
		int i;
		float f;
	} u;

	u.f = 12.34;		/* assign a floating point value */
	printf("%f also look like %#x\n", u.f, u.i);

	exit(0);
}
