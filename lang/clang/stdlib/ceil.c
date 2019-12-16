#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	div_t total = { 0, 0 };
	int count = 17;
	int price = 9999;
	double vat_rate = 0.055;
	total = div((int)ceil((count * price) * (1 + vat_rate)), 100);
	printf("Total due: $%d.%2d\n", total.quot, total.rem);
	return 0;
}
