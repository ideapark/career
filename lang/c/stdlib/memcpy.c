#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct record {
	char name[32];
	double data;
	struct record *next;
	struct record *prev;
} Rec_t;

int main(void)
{
	Rec_t template = { "Another fine product", -0.0, NULL, NULL };
	Rec_t *tmp_new;

	if ((tmp_new = (Rec_t *) malloc(sizeof(Rec_t))) != NULL)
		memcpy(tmp_new, &template, sizeof(Rec_t));
	else {
		fprintf(stderr, "Out of memory!\n");
		return -1;
	}

	/* print result */
	printf("name: %s\ndata: %f\n", template.name, template.data);
	printf("name: %s\ndata: %f\n", tmp_new->name, tmp_new->data);
	assert(tmp_new->next == NULL);
	assert(tmp_new->prev == NULL);

	free(tmp_new);
	tmp_new = NULL;

	return 0;
}
