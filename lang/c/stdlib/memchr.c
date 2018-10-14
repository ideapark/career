#include <string.h>
#include <stdio.h>

int main(void)
{
	char *found;
	char buffer[4096] = "";
	int ch = ' ';

	fgets(buffer, sizeof(buffer), stdin);
	printf("Before: %s", buffer);
	while ((found = memchr(buffer, ch, strlen(buffer))) != NULL)
		*found = '_';
	printf("After : %s", buffer);

	return 0;
}
