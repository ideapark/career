#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <error.h>

/*
 * Return 1 if PATH is a usable leading directory, 0 if not,
 * 2 if it doesn't exist.
 */
static int dir_ok(const char *path)
{
	struct stat stats;

	if (stat(path, &stats))
		return 2;

	if (!S_ISDIR(stats.st_mode)) {
		error(0, 0, "'%s' is not a directory", path);
		return 0;
	}

	/*
	 * Use access to test for search permission because
	 * testing permission bits of st_mode can lose with new
	 * access control mechanisms. Of course, access loses if
	 * you're running setuid.
	 */
	if (access(path, X_OK) != 0) {
		if (errno == EACCES)
			error(0, 0, "directory '%s' is not searchable", path);
		else
			error(0, errno, "%s", path);
		return 0;
	}

	return 1;
}
