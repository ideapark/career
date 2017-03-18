// float.c -- display float precise
// --------------------------------------------------------------------

#include <stdio.h>
#include <float.h>

int main(void)
{
	puts("\nCharacteristics of the type float\n");
	printf("Storage size: %d bytes\n"
	       "Smallest positive value: %E\n"
	       "Greatest positive value: %E\n"
	       "Precision: %d decimal digits\n",
	       sizeof(float), FLT_MIN, FLT_MAX, FLT_DIG);

	puts("\nAn example of float precision:\n");
	double d_var = 12345.6;     // double
	float f_var = (float)d_var; // init f_var with d_var
	printf("The floating-point number    "
	       "%18.10f\n", d_var);
	printf("has been stored in a variable\n"
	       "of type float as the value    "
	       "%18.10f\n", f_var);
	printf("The rounding error is    "
	       "%18.10f\n", d_var - f_var);

	return 0;
}
