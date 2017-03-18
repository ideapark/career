/*
 * Print the Target of a Symbolic Link
 */

#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	char target_path[256];
	char *link_path = argv[1];

	/* Attempt to read the target of the symbolic link. */
	int len = readlink(link_path, target_path, sizeof(target_path));

	if (len == -1) {
		/* The call failed. */
		if (errno == EINVAL)
			fprintf(stderr, "%s is not a symbolic link\n", link_path);
		else
			perror("readlink");
		return 1;
	} else {
		/* readlink does not NUL-terminate the target path, It does, however,
		   return the number of characters in the target path. */
		target_path[len] = '\0';
		printf("%s\n", target_path);
		return 0;
	}
}
