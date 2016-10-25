#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	struct stat statbuf;
	char *type, *readok;

	if (stat(argv[1], &statbuf) < 0)
		return -1;

	if (S_ISREG(statbuf.st_mode))
		type = "regular";
	else if (S_ISDIR(statbuf.st_mode))
		type = "directory";
	else
		type = "other";

	if (statbuf.st_mode & S_IRUSR)
		readok = "yes";
	else
		readok = "no";

	printf("type: %s, read: %s\n", type, readok);
	return 0;
}
