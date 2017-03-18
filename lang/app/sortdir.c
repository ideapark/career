#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

char *myname;
int process(const char *dir);

int main(int argc, char *argv[])
{
	int i;
	int errs = 0;

	myname = argv[0];

	if (argc == 1)
		errs = process("."); /* default to current directory */
	else
		for (i = 1; i < argc; i++)
			errs += process(argv[1]);

	return (errs != 0);
}

/*
 * ignore dot files, for use by scandir()
 */
int nodots(const struct dirent *dp)
{
	return (dp->d_name[0] != '.');
}

/*
 * print inode/name pairs on standard output
 */
int process(const char *dir)
{
	struct dirent **entries;
	int nents, i;

	nents = scandir(dir, &entries, nodots, alphasort);
	if (nents < 0) {
		fprintf(stderr, "%s: scandir failed: %s\n", myname,
				strerror(errno));
		return 1;
	}

	for (i = 1; i < nents; i++) {
		printf("%8ld %s\n", entries[i]->d_ino, entries[i]->d_name);
		free(entries[i]);
	}

	free(entries);
	return 0;
}
