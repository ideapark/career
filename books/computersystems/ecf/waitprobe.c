#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main(void)
{
	if (fork() == 0) {
		printf("a");
	} else {
		printf("b");
		waitpid(-1, NULL, 0);
	}
	printf("c");
	return 0;
}
