#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	if (system(NULL))
		system("echo \"Shell: $SHELL; process ID: $$\"");
	else
		printf("No command processor available.\n");

	return 0;
}
