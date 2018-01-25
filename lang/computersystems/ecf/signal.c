#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handler(int sig)
{
	pid_t pid;

	while ((pid = waitpid(-1, NULL, 0)) > 0)
		printf("Handler reaped child %d\n", (int)pid);
	if (errno != ECHILD) {
		fprintf(stderr, "waitpid error: %s\n", strerror(errno));
		exit(0);
	}
	sleep(2);
}

int main(void)
{
#define MAXBUF  256
	int i, n;
	char buf[MAXBUF];
	pid_t pid;

	if (signal(SIGCHLD, handler) == SIG_ERR) {
		fprintf(stderr, "signal error: %s\n", strerror(errno));
		exit(0);
	}

	for (i = 0; i < 3; i++) {
		pid = fork();
		if (pid == 0) {
			printf("Hello from child %d\n", (int)getpid());
			sleep(1);
			exit(0);
		}
	}

	while ((n = read(STDIN_FILENO, buf, sizeof(buf))) < 0)
		if (errno != EINTR) {
			fprintf(stderr, "read error: %s\n", strerror(errno));
			exit(0);
		}

	printf("Parent processing input\n");
	while (1)
		;

	return 0;
}
