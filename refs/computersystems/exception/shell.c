#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function prototypes */
void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);

extern char **environ;

#define MAXLINE  256
#define MAXARGS  16

int main(void)
{
	char cmdline[MAXLINE];  /* Command line */

	while (1) {
		printf("> ");
		fgets(cmdline, MAXLINE, stdin);
		if (feof(stdin))
			exit(0);
		/* Evaluate */
		eval(cmdline);
	}
	return 0;
}

/* eval -- Evaluate a command line */
void eval(char *cmdline)
{
	char *argv[MAXARGS];  /* Argument list execve() */
	char buf[MAXLINE];    /* Holds modified command line */
	int bg;               /* Should the job run in bg or fg? */
	pid_t pid;            /* Process id */

	strcpy(buf, cmdline);
	bg = parseline(buf, argv);
	if (argv[0] == NULL)
		return;  /* Ignore empty lines */

	if (!builtin_command(argv)) {
		if ((pid = fork()) == 0) {  /* Child runs user job */
			if (execve(argv[0], argv, environ) < 0) {
				printf("%s: Command not found.\n", argv[0]);
				exit(0);
			}
		}

		/* Parent waits for foreground job to terminate */
		if (!bg) {
			int status;
			if (waitpid(pid, &status, 0) < 0) {
				fprintf(stderr, "waitfg: waitpid error: %s.\n", strerror(errno));
				exit(-1);
			}
		} else {
			printf("%d %s", pid, cmdline);
		}
	}
}

/* If first arg is a builtin command, run it and return true */
int builtin_command(char **argv)
{
	if (!strcmp(argv[0], "quit"))
		exit(0);
	if (!strcmp(argv[0], "&"))
		return 1;
	return 0;
}

/* parseline -- Parse the command line and build the argv array */
int parseline(char *buf, char **argv)
{
	char *delim; /* Points to first space delimiter */
	int argc;    /* Number of args */
	int bg;      /* Background job? */

	buf[strlen(buf)-1] = ' '; /* Replace trailing '\n' with space */
	while (*buf && (*buf == ' ')) /* Ignore leading spaces */
		buf++;

	/* Build the argv list */
	argc = 0;
	while ((delim = strchr(buf, ' '))) {
		argv[argc++] = buf;
		*delim = '\0';
		buf = delim + 1;
		while (*buf && (*buf == ' '))
			buf++;
	}
	argv[argc] = NULL;

	if (argc == 0)
		return 1;

	if ((bg = (*argv[argc-1] == '&')) != 0)
		argv[--argc] = NULL;

	return bg;
}
