#include <stdio.h>

#define MEGABYTE (1024 * 1024)

int main(int argc, char *argv[])
{
	void *block = NULL;
	int count = 0;
	
	while (1) {
		block = (void *)malloc(MEGABYTE);
		if (!block)
			break;
		printf("Currently allocating %d MB\n", ++count);
	}
	getchar();
	return 0;
}
