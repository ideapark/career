#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int c;
	FILE *in, *out;

	in = fopen("around-the-world-in-80-days.txt", "r");
	out = fopen("/tmp/around.out", "w");
	while ((c = fgetc(in)) != EOF) {
		fputc(c, out);
	}
	return 0;
}
