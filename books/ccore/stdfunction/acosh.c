#include <math.h>
#include <stdio.h>
#include <errno.h>

int main(void)
{
	double x, y1, y2;
	puts("acosh(x) is equal to log(x+sqrt(x*x-1))\n");
	puts("For the argument x, enter some numbers greater than or equal to 1.0"
			"\n(type any letter to quit:)");
	while (scanf("%lf", &x) == 1) {
		errno = 0;
		y1 = acosh(x);
		if (errno == EDOM) {
			perror("acosh");
			break;
		}
		y2 = log(x+sqrt(x*x-1));
		printf("x = %f; acosh(x) = %f; log(x+sqrt(x*x-1)) = %f\n", x, y1, y2);
	}
	return 0;
}
