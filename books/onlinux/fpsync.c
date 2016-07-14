/* fpsync --- sync a stdio FILE * variable */

#include <unistd.h>
#include <stdio.h>

int fpsync(FILE *fp)
{
	if (fp == NULL || fflush(fp) == EOF || fsync(fileno(fp)) < 0)
		return -1;

	return 0;
}
