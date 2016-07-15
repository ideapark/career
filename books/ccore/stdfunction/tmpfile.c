#include <stdio.h>

int main(void)
{
	FILE *fpTmp;
	FILE *fpRx;
	int c;

	if ((fpRx = fopen("./tmpfile.c", "r+")) == NULL) {
		fprintf(stderr, "Can't open file \"./tmpfile.c\" to read.\n");
		return -1;
	}

	if ((fpTmp = tmpfile()) == NULL)
		fputs("Unable to open a temporary file.", stderr);
	else {
		while ((c = fgetc(fpRx)) != EOF)
			if (fputc(c, fpTmp) == EOF)
				break;
	}

	fclose(fpRx), fpRx = NULL;
	fclose(fpTmp), fpTmp = NULL;

	return 0;
}
