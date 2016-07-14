#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int pipefd[2];

extern void left_child(void);
extern void right_child(void);

int main(int argc, char *argv[])
{
	pid_t left_pid, right_pid;
	pid_t ret;
	int status;

	if (pipe(pipefd) < 0) { /* create pipe, very first thing */
		perror("pipe");
		exit(1);
	}

	if ((left_pid = fork()) < 0) { /* fork left-hand child */
		perror("fork");
		exit(1);
	} else if (left_pid == 0) {
		left_child();
	}

	if ((right_pid = fork()) < 0) { /* fork right-hand child */
		perror("fork");
		exit(1);
	} else if (right_pid == 0) {
		right_child();
	}

	close(pipefd[0]); /* close parent's copy of pipe */
	close(pipefd[1]);

	while ((ret = wait(&status)) > 0) {
		if (ret == left_pid)
			printf("left child terminated, status: %x\n", status);
		else if (ret == right_pid)
			printf("right child terminated, status: %x\n", status);
		else
			printf("yow! unknown child %d terminated, status %x\n",
					ret, status);
	}

	return 0;
}

void left_child(void)
{
	static char *left_argv[] = {"echo", "hi", "there", NULL};

	close(pipefd[0]);
	close(1);
	dup(pipefd[1]);
	close(pipefd[1]);

	execvp("echo", left_argv);
	_exit(errno == ENOENT ? 127 : 126);
}

void right_child(void)
{
	static char *right_argv[] = {"sed", "s/hi/hello/g", NULL};

	close(pipefd[1]);
	close(0);
	dup(pipefd[0]);
	close(pipefd[0]);

	execvp("sed", right_argv);
	_exit(errno == ENOENT ? 127 : 126);
}
