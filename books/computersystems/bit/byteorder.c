#include <stdio.h>

void show_bytes(unsigned char *start, int len)
{
	int i;

	for (i = 0; i < len; i++)
		printf(" %.2x", start[i]);
	printf("\n");
}

void show_int(int x)
{
	show_bytes((unsigned char *)&x, sizeof(int));
}

void show_float(float x)
{
	show_bytes((unsigned char *)&x, sizeof(float));
}

void show_pointer(void *x)
{
	show_bytes((unsigned char *)&x, sizeof(void *));
}

int main(void)
{
	char c = 'A';
	int i = 1024;
	float f = 1024.0;
	char *p = &c;

	show_int(i);
	show_float(f);
	show_pointer(p);

	return 0;
}
