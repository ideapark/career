#include <stdio.h>

int main(void)
{
	FILE *fp;
	int c;
	char buffer[1024];
	int i = 0;

	fp = fopen("fgetc.c", "r+");
	if (fp == NULL) {
		fprintf(stderr, "fget.c: file open falied.\n");
		return -1;
	}

	while (i < 1023) {
		c = fgetc(fp);	/* return a char on success */
		if (c == EOF) {	/* EOF means reached end of file */
			if (feof(fp))
				fprintf(stderr, "End of input.\n");
			else if (ferror(fp))
				fprintf(stderr, "Input error.\n");
			clearerr(fp);	/* clear file error or EOF */
			break;
		} else {
			buffer[i++] = (char)c;	/* after EOF checked can be converted to char safely */
		}
	}
	buffer[i] = '\0';
	puts(buffer);

	return 0;
}
