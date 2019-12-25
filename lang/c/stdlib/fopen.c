#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	FILE *in, *out;
	int c;

	if (argc != 3) {
		fprintf(stderr, "Usage: program input-file output-file\n");
		exit(1);
	}

	/* input file "-" equal to stdin */
	in = (strcmp(argv[1], "-") == 0) ? stdin : fopen(argv[1], "r");
	if (in == NULL) {
		perror("Opening input file");
		return -1;
	}

	/* output file "-" equal to stdout */
	out = (strcmp(argv[2], "-") == 0) ? stdout : fopen(argv[2], "a+");
	if (out == NULL) {
		perror("Opening output file");
		return -1;
	}

	while ((c = fgetc(in)) != EOF)
		if (fputc(c, out) == EOF)
			break;
	if (!feof(in))
		perror("Error while copying");

	fclose(in);
	fclose(out);

	return 0;
}
