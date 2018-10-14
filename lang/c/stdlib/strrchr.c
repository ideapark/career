#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	char *mybasename = strrchr(argv[0], '/' /* '\\' for Windows */ );	/* find the end char of string (Unix/Linux) */
	if (mybasename != NULL)
		mybasename++;	/* pointed to the char after the slash char */
	else
		mybasename = argv[0];
	printf("This program was invoked as %s.\n", mybasename);

	return 0;
}
