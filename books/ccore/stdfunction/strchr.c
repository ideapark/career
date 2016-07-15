#include <string.h>
#include <stdlib.h>

typedef struct {
	char street[32];
	char city[32];
	char stateprovince[32];
	char zip[16];
} Address;

int main(void)
{
	char printaddr[128] = "720 S. Michigan Ave.\nChicago, IL 60605\n";
	int sublength;
	Address *newAddr = calloc(1, sizeof(Address));

	if (newAddr != NULL) {
		sublength = strchr(printaddr, '\n') - printaddr;
		strncpy(newAddr->street, printaddr, (sublength < 31 ? sublength : 31));
		free(newAddr);
		newAddr = NULL;
	}
	return 0;
}
