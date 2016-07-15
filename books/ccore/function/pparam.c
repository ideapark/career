#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct Node {
	long key;
	char name[32];
	struct Node *next;
};

void initNode(struct Node *pNode)
{
	memset(pNode, 0, sizeof(*pNode));
	strcpy(pNode->name, "XXXXX");
}

void printNode(const struct Node *pNode)
{
	printf("Key: %ld\n", pNode->key);
	printf("Name: %s\n", pNode->name);
}

struct Node* mkNode()
{
	struct Node *pNode = malloc(sizeof(struct Node));
	if (pNode != NULL)
		initNode(pNode);
	return pNode;
}

int main(void)
{
	struct Node *header = NULL;
	struct Node *current = NULL;
	for (int i = 0; i < 100; ++i) {
		struct Node *pnew = mkNode();
		if (header == NULL)
			header = current = pnew;
		else {
			current->next = pnew;
			current = pnew;
		}
	}

	current = header;
	while (current != NULL) {
		printNode(current);
		header = current;
		current = current->next;
		free(header);
	}
	return 0;
}
