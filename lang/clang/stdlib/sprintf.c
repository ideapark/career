#include <stdio.h>

int main(void)
{
	char buffer[80];
	double x = 1234.5;
	double y = 678.9;
	double z = -753.1;
	double a = x * y + z;
	int output_len = 0;

	output_len = sprintf(buffer, "For the input value %lf, %lf and %lf, "
			     "the result was %lf.\n", x, y, z, a);
	puts(buffer);

	if (output_len >= 80)
		fprintf(stderr, "Output string overflowed by %d characters.\n"
			"The variables x, y, z and a may have been corrupted:\n"
			"x now contains %lf, y %lf, z %lf, and a %lf.\n",
			output_len - 79, x, y, z, a);

	return 0;
}
