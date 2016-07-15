#include <string.h>
#include <stdio.h>

int main(void)
{
	char wordin[256];
	double val;

	puts("Enter a float-point number, please:");
	scanf("%s", wordin);

	int index = strspn(wordin, "+-0123456789eE.");
	if (index < strlen(wordin))
		printf("Sorry, but the character %c is not permitted.\n", wordin[index]);
	else {
		sscanf(wordin, "%lg", &val);
		printf("You entered the value %g\n", val);
	}

	return 0;
}
