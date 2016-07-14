#include <unistd.h>

int main(void)
{
	/* example of an argument list
	   note that we need a program name for argv[0] */
	char *const ps_argv[] = {
		"ps",
		"ax",
		0
	};

	/* example environment, not terribly useful */
	char *const ps_envp[] = {
		"PATH=/bin:/usr/bin",
		"TERM=console",
		0
	};

	/* possible calls to exec functions */
	execl("/bin/ps", "ps", "ax", (char *)0); /* assumes ps is in /bin */
	execlp("ps", "ps", "ax", (char *)0);     /* assumes /bin is in PATH */
	execle("/bin/ps", "ps", "ax", (char *)0, ps_envp); /* passes own environment */

	execv("/bin/ps", ps_argv);
	execvp("ps", ps_argv);
	execve("/bin/ps", ps_argv, ps_envp);

	return 0;
}
