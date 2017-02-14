#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	char dotted[] = "172.16.2.10";
	char *ptr = dotted;
	char *nextdot = NULL;
	unsigned long dest = 0;

	for (int i = 0; i < 4; i++) {
		dest << 8;
		dest += strtoul(ptr, &nextdot, 10);
		ptr = nextdot + 1;
	}
	printf("172.16.2.10 = %lu\n", dest);

	return 0;
}
