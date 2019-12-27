/*
 * Demonstrate setjmp()/longjmp() and volatile.
 */

#include <stdio.h>
#include <setjmp.h>

jmp_buf env;

void comeback(void)
{
	longjmp(env, 1);
	printf("This line is never printed\n");
}

int main(void)
{
	int i = 5;
	volatile int j = 6;

	if (setjmp(env) == 0) {	/* first time */
		i++;
		j++;
		printf("first time: i = %d, j = %d\n", i, j);
		comeback();
	} else {		/* second time */
		printf("second time: i = %d, j = %d\n", i, j);
	}

	return 0;
}
