#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define N  20

int main(void)
{
	int status, i;
	pid_t pid;

	/* Parent creates N children */
	for (i = 0; i < N; i++)
		if ((pid = fork()) == 0) /* child */
			exit(100+i);

	/* Parent reaps N children in no particular order */
	while ((pid = waitpid(-1, &status, 0)) > 0) {
		if (WIFEXITED(status))
			printf("child %d terminated normally with exit status=%d\n",
			       pid, WEXITSTATUS(status));
		else
			printf("child %d terminated", pid);
	}

	/* The only normal termination is if there are no more children */
	if (errno != ECHILD) {
		fprintf(stderr, "waitpid error: %s\n", strerror(errno));
		exit(-1);
	}
	return 0;
}
