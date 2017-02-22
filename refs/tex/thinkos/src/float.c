#include <stdio.h>
#include <stdlib.h>

union {
	float f;
	unsigned int u;
} p;

int main()
{
	p.f = -13.0;
	unsigned int sign = (p.u >> 31) & 1;
	unsigned int exp = (p.u >> 23) & 0xff;

	unsigned int coef_mask = (1 << 23) - 1;
	unsigned int coef = p.u & coef_mask;

	printf("sign: %d\n", sign);
	printf(" exp: %d\n", exp);
	printf("coef: 0x%x\n", coef);

	return 0;
}
