#include <stdio.h>
#include <stdlib.h>

int main(void)
{
#define MAX_LINE096
	FILE *fp_linewise = fopen("output.txt", "a+");
	char *iobuffer = (char *)malloc(MAX_LINE);

	if (iobuffer != NULL) {
		/* NOTE:
		 *      setvbuf() should be called after file opened
		 *      successfully and before any io operation
		 */
		/*
		 * _IOFBF: full buffer
		 *
		 * _IOLBF: line buffer
		 *
		 * _IONBF: no buffer
		 */
		if (setvbuf(fp_linewise, iobuffer, _IOLBF, MAX_LINE)) {
			fprintf(stderr,
				"setvbuf() failed; unable to set line-buffering.\n");
			free(iobuffer);	/* release resource */
			iobuffer = NULL;
			exit(-2);
		}

		/* write something to file */

		fclose(fp_linewise);
		free(iobuffer);
		iobuffer = NULL;
	} else {
		fprintf(stderr,
			"malloc() failed; no point in calling setvbuf().\n");
		exit(-1);
	}

	return 0;
}
