/*
 * LICENSE: GPL
 *
 * demo_userns.c
 *
 * Demonstrate the use of the clone() CLONE_NEWUSER flag.
 *
 * Link with "-lcap" and make sure that the "libcap-devel" (or
 * similar) package is installed on the system.
 *
 * See https://lwn.net/Articles/532593/
 */
#define _GNU_SOURCE
#include <sys/capability.h>
#include <sys/wait.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define errExit(msg)						\
	do { perror(msg); exit(EXIT_FAILURE); } while (0)

/* Startup function for cloned child */
static int childFunc(void *arg)
{
	cap_t caps;

	for (;;) {
		printf("eUID = %ld; eGID = %ld; ",
		       (long) geteuid(), (long) getegid());

		caps = cap_get_proc();
		printf("capabilities: %s\n", cap_to_text(caps, NULL));

		if (arg == NULL)
			break;

		sleep(5);
	}

	return 0;
}

#define STACK_SIZE (1024 * 1024)

static char child_stack[STACK_SIZE];    /* Space for child's stack */

int main(int argc, char *argv[])
{
	pid_t pid;

	/* Create child; child commences execution in childFunc() */

	pid = clone(childFunc, child_stack + STACK_SIZE,    /* Assume stack
							       grows downward */
		    CLONE_NEWUSER | SIGCHLD, argv[1]);
	if (pid == -1)
		errExit("clone");

	printf("PID of child: %ld\n", (long) pid);

	/* Parent falls through to here.  Wait for child. */

	if (waitpid(pid, NULL, 0) == -1)
		errExit("waitpid");

	exit(EXIT_SUCCESS);
}
