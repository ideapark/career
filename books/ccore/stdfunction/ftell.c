#include <stdio.h>
#include <stdlib.h> /* exit() */
#include <string.h>

#define MAX_LINE 256

int main(int argc, char *argv[])
{
	FILE *fp;
	long lOffset = 0L;
	char sLine[MAX_LINE] = "";
	int lineno = 0;

	if ((fp = fopen(argv[2], "r")) == NULL) {
		fprintf(stderr, "Unable to open file %s\n", argv[2]);
		exit(-1);
	}

	do {
		lOffset = ftell(fp); /* Bookmark the beginning of the
					line we're about to read */
		if (-1L == lOffset)
			fprintf(stderr, "Unable to obtain offset in %s\n", argv[2]);
		else
			lineno++;

		if (!fgets(sLine, MAX_LINE, fp)) { /* Read next line from file. */
			fprintf(stderr, "Unable to read from %s\n", argv[2]);
			break;
		}
	} while (strstr(sLine, argv[1]) == NULL); /* Test for argument in sLine */

	/* Droppped out of loop: Found search keyword of EOF */
	if (feof(fp)) {
		fprintf(stderr, "Unable to find \"%s\" in %s\n", argv[1], argv[2]);
		rewind(fp);
	} else {
		printf("%s (%d): %s\n", argv[2], lineno, sLine);
		fseek(fp, lOffset, 0); /* Set file pointer at beginning of
					  the line containing the keyword */
	}

	return 0;
}
