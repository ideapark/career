#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct linelink {
	char *line;
	struct linelink *next;
};

enum ErrorCode {
	FILE_NOT_EXIST = 1, /* file not exist */
	OUT_OF_MEMORY  = 2  /* out of memory */
};

int main(void)
{
	struct linelink *head = NULL;
	struct linelink *tail = NULL;
	char buffer[2048];
	FILE *fp_in;

	if ((fp_in = fopen("malloc.c", "r")) == NULL) {
		perror("malloc.c");
		return FILE_NOT_EXIST;
	}

	while (NULL != fgets(buffer, sizeof(buffer), fp_in)) {
		struct linelink* new_node = (struct linelink*)malloc(sizeof(struct linelink));
		if (new_node == NULL) {
			fprintf(stderr, "Out of memory\n");
			return OUT_OF_MEMORY;
		}

		new_node->line = (char*)malloc(strlen(buffer)+1);
		if (new_node->line != NULL)
			strcpy(new_node->line, buffer);
		else {
			fprintf(stderr, "Out of memory\n");
			return OUT_OF_MEMORY;
		}
		new_node->next = NULL;

		if (head == NULL && tail == NULL) /* first node */
			head = tail = new_node;
		else { /* append to tail */
			tail->next = new_node;
			tail = new_node;
		}
	}

	/* print list */
	struct linelink *pnode = head;
	while (pnode != NULL) {
		printf("%s", pnode->line);
		pnode = pnode->next;
	}

	/* destroy list */
	while ((pnode = head) != NULL) {
		head = head->next;
		free(pnode->line); /* free data line */
		free(pnode); /* free node */
	}

	return 0;
}
