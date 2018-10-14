#include <stdio.h>
#include <string.h>

int main(void)
{
	struct guest {
		char name[64];
		int age;
		_Bool male;
		_Bool smoking;
		_Bool discount;
	} this;
	int result;

	printf("Last name: ");
	result = scanf("%s[^\n]", this.name);
	if (result < 1)
		strcpy(this.name, "[not available]");

	return 0;
}
