/*
 * LICENSE: GPL
 *
 * orphan.c
 *
 * Demonstrate how a child becomes orphaned (and adopted by init(8),
 * whose PID is 1) when its parent exits.
 */
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
	pid_t ppid;

	setbuf(stdout, NULL);       /* Disable buffering of stdout */

	switch (fork()) {
	case -1:
		errExit("fork");

	case 0:             /* Child */
		while ((ppid = getppid()) != 1) {   /* Loop until orphaned */
			printf("Child running (parent PID=%ld)\n", (long) ppid);
			sleep(1);
		}
		printf("Child is orphaned (parent PID=%ld)\n", (long) ppid);
		_exit(EXIT_SUCCESS);

	default:            /* Parent */
		printf("Parent (PID=%ld) sleeping\n", (long) getpid());
		sleep(3);                           /* Give child a chance to start */
		printf("Parent exiting\n");
		exit(EXIT_SUCCESS);
	}
}
