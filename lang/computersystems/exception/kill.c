#include <unistd.h>
#include <signal.h>
#include <stdio.h>

int main(void)
{
	pid_t pid;

	if ((pid = fork()) == 0) {
		pause();
		printf("control should never reach here!\n");
		exit(0);
	}

	kill(pid, SIGKILL);
	return 0;
}
