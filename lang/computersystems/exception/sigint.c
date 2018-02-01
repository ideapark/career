#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handler(int sig)
{
	printf("Caught SIGINT\n");
	exit(0);
}

int main(void)
{
	if (signal(SIGINT, handler) == SIG_ERR) {
		fprintf(stderr, "signal error: %s\n", strerror(errno));
		exit(-1);
	}

	pause();
	exit(0);
}
