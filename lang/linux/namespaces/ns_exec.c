/*
 * LICENSE: GPL
 *
 * ns_exec.c
 *
 * Join a namespace using setns() and execute a command in the namespace.
 * This is program is similar in concept to nsenter(1) (however, that
 * program allows multiple namespaces to be joined), but has a less
 * command-line interface.
 *
 * See https://lwn.net/Articles/531381/
 */
#define _GNU_SOURCE
#include <fcntl.h>
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/wait.h>

/* A simple error-handling function: print an error message based
   on the value in 'errno' and terminate the calling process */

#define errExit(msg)						\
	do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[])
{
	int fd;

	if (argc < 3) {
		fprintf(stderr, "%s /proc/PID/ns/FILE cmd [arg...]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	fd = open(argv[1], O_RDONLY);   /* Get descriptor for namespace */
	if (fd == -1)
		errExit("open");

	if (setns(fd, 0) == -1)         /* Join that namespace */
		errExit("setns");

	execvp(argv[2], &argv[2]);      /* Execute a command in namespace */
	errExit("execvp");
}
