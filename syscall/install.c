#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * Strip the symbol table from the file PATH. We could dig
 * the magic number out of the file first to determine
 * whether to strip it, but the header files and magic
 * numbers vary so much from system to system that making
 * portable would be very difficult. Not worth the effort.
 */
static void strip(const char *path)
{
	int status;
	pid_t pid = fork();

	switch (pid) {
	case -1:
		error(EXIT_FAILURE, errno, _("fork system call failed"));
		break;
	case 0:		/* child */
		execlp("strip", "strip", path, NULL);
		error(EXIT_FAILURE, errno, _("cannot run strip"));
		break;
	default:		/* parent */
		while (pid != wait(&status))
			/* wait for kid to finish */
			/* do nothing */
			;
		if (status)
			error(EXIT_FAILURE, 0, _("strip failed"));
		break;
	}
}
