#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int c;
	FILE *fp;

	if ((fp = fopen("putc.c", "r+")) == NULL) {
		fprintf(stderr, "Couldn't open input file.\n");
		exit(-1);
	}

	while ((c = getc(fp)) != EOF) {	/* read until EOF */
		if (c == '@') {
			fseek(fp, -1, SEEK_CUR);	/* bakup this char */
			putc('$', fp);	/* replaced with '$' */
			fflush(fp);
		}
	}
	fclose(fp);

	return 0;
}
