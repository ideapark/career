#include <stdlib.h>
#include <stdio.h>

struct record {
	long id;
	int data[256];
	struct record *next;
};

int main(void)
{
	struct record *pnew = (struct record *)malloc(sizeof(struct record));
	if (pnew == NULL) {	/* check malloc */
		fprintf(stderr, "%s: out of memory!", __func__);
		abort();	/* send SIGABRT signal */
	}
	return 0;
}
