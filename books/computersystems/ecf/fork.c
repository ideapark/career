#include "unistd.h"
#include "errno.h"
#include "stdio.h"
#include "string.h"

int main(void)
{
	pid_t pid;
	int x = 1;

	pid = fork();
	if (pid > 0) {
		printf("parent: x=%d\n", --x);
	} else if (pid == 0) {
		printf("parent: x=%d\n", ++x);
	} else {
		fprintf(stderr, "%s", strerror(errno));
	}
	return 0;
}
