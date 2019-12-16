#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char lastname[32];
	char firstname[32];
	_Bool ismale;
} Name;

int main(void)
{
	char displayname[80];
	Name *newName = calloc(1, sizeof(Name));

	if (newName == NULL) {
		fprintf(stderr, "Out of memory!\n");
		return -1;
	}

	strcpy(displayname, (newName->ismale ? "Mr. " : "Ms. "));
	strcat(displayname, newName->firstname);
	strcat(displayname, " ");
	strcat(displayname, newName->lastname);
	puts(displayname);

	free(newName);
	newName = NULL;

	return 0;
}
