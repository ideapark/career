#include <string.h>
#include <stdio.h>

int main(void)
{
	char line[1024] = "This string could easily be hundreds "
		"of characters long. Suddenly, I fell "
		"in love with her, She is so charming "
		"so sweet, so pride, so cold, so smart "
		"so beautiful.";
	char *readptr = line;
	int columns = 80;

	while (strlen(readptr) > columns) {
		printf("%.*s\\", columns-1, readptr);
		readptr += columns-1;
	}
	printf("%s\n", readptr);

	return 0;
}
