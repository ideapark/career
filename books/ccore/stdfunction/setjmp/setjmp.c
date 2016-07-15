#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include <errno.h>

#include "calc.h"

jmp_buf jmp_dest; /* destination of longjmp() */

int main(void)
{
	double x = 0, y1, y2;
	int n = 0;

	puts("--- Demonstrating non-local jumps ---\n");

	switch (setjmp(jmp_dest)) { /* jump here to error handling */
		case 0:      /* initial call to setjmp() */
			break;
		case EDOM:   /* longjmp() by EDOM */
			puts("Domain error. "
					"Negative numbers are not permitted.");
			break;
		case ERANGE: /* longjmp() by ERANGE */
			puts("Range error. "
					"The number you entered is too big.");
			break;
		default:     /* shouldn't get here!!! */
			puts("Unknown error.");
			exit(EXIT_FAILURE);
	}

	printf("Enter a number: ");

	do {
		if ((n = scanf("%lf", &x)) < 0) /* read a number */
			exit(EXIT_FAILURE);
		while (getchar() != '\n') /* read until EOF, clear input buffer */
			;
		if (n == 0)
			printf("Invalid entry. Try again: ");
	} while (n == 0);

	y1 = calculate1(x);
	y2 = calculate2(x);

	printf("\nResult of Calculation 1: %G\n", y1);
	printf(  "Result of Calculation 2: %G\n", y2);

	return 0;
}
