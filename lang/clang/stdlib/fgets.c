#include <stdio.h>

int main(void)
{
	char buffer[1024];

	/* fgets() is safer than gets() */
	while (fgets(buffer, sizeof(buffer), stdin) != NULL)
		printf("%s\n", buffer);

	return 0;
}
