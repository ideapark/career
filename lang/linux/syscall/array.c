#include <stdio.h>

#define EINVAL  1
#define ENOMEM  2
#define EFAULT  3
#define E2BIG   7
#define EBUSY   8
#define ECHILD  12

static char *err_strings[] = {
	[0] = "Success",
	[EINVAL] = "Invalid argument",
	[ENOMEM] = "Not enough memory",
	[EFAULT] = "Bad address",
	[E2BIG] = "Argument list too long",
	[EBUSY] = "Device or resource busy",
	[ECHILD] = "No child processes"
};

int main(int argc, char *argv[])
{
	int i;

	for (i = 0; i < sizeof(err_strings)/sizeof(err_strings[0]); i++)
		printf("%-3d - %s\n", i, err_strings[i]);

	return 0;
}
