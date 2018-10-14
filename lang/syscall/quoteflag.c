/*
 * Demonstrate printf's quote flag
 */

#include <stdio.h>
#include <locale.h>

int main(void)
{
	setlocale(LC_ALL, "");	/* have to do this, or it won't work */
	printf("%'d\n", 1234567);
	return 0;
}
