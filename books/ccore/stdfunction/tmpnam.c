#include <stdio.h>

int main(void)
{
	char buffer[L_tmpnam];
	char *name = buffer;
	FILE *fpOut;
	int result;

	name = tmpnam(buffer);
	if (name == NULL) {
		fputs("Failed to generate temporary file name", stderr);
		return -1;
	}

	fpOut = fopen(name, "w+");
	if (fpOut == NULL) {
		fprintf(stderr, "Failed to open file to write.\n");
		return -2;
	}

	result = fwrite("I love you\n", 1, 11, fpOut);
	fclose(fpOut);
	printf("Results saved in %s\n", name);

	return 0;
}
