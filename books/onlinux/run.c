#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	char *path;

	if (argc < 3) {
		fprintf(stderr, "usage: %s path arg0 [arg ...]\n", argv[0]);
		exit(1);
	}

	path = argv[1];

	execv(path, argv + 2); /* skip argv[0] and argv[1] */
	fprintf(stderr, "%s: execv() failed: %s\n", argv[0],
			strerror(errno));

	exit(0);
}
