/*
 * probe default char signess
 */

#include <stdio.h>

int main(void)
{
	/*
	 * most archetecture char is signed, range from -128 to 127
	 * but some archetecture (like ARM) char is unsigned range
	 * from 0 to 255
	 */
	char c = -1;
	printf("%d\n", (int)c);

	return 0;
}
