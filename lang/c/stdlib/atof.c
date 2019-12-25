#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	char string[] = " -1.02857e+2 \260C";	// *C
	double z;
	z = atof(string);
	printf("\"%s\" becomes %.2f\n", string, z);
	return 0;
}
