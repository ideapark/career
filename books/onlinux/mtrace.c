/*
 * Demonstrate usage of mtrace()/muntrace()
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mcheck.h>

static char *hl = "hello, world.\n";

void alloc_then_leak()
{
	char *ptr;

	ptr = (char *)malloc(BUFSIZ);
	if (ptr == NULL) {
		fprintf(stderr, "cannot allocate memory.\n");
		exit(1);
	}

	strcpy(ptr, hl);
	printf("%s: %d: %s", __FILE__, __LINE__, ptr);
}

void alloc_then_free()
{
	char *ptr;

	ptr = (char *)malloc(BUFSIZ);
	if (ptr == NULL) {
		fprintf(stderr, "cannot allocate memory.\n");
		exit(1);
	}

	strcpy(ptr, hl);
	printf("%s: %d: %s", __FILE__, __LINE__, ptr);
	free(ptr);
}

int main(void)
{
	int i;
	const int loop = 5;

	mtrace(); /* enable glibc memory debug */

	for (i = 0; i < loop; i++) {
		alloc_then_leak();
		alloc_then_free();
	}

	muntrace(); /* disable glibc memory debug */

	return 0;
}
