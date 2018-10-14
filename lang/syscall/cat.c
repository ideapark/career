#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

char *myname;

static int process(char *file)
{
	int fd;
	int errors = 0;
	char buffer[BUFSIZ];
	ssize_t rcount, wcount;

	if (strcmp(file, "-") == 0)
		fd = 0;
	else if ((fd = open(file, O_RDONLY)) < 0) {
		fprintf(stderr, "%s: %s: cannot open for reading: %s\n",
			myname, file, strerror(errno));
		return 1;
	}

	while ((rcount = read(fd, buffer, sizeof(buffer))) > 0) {
		wcount = write(1, buffer, rcount);
		if (wcount != rcount) {
			fprintf(stderr, "%s: %s: write error: %s\n",
				myname, file, strerror(errno));
			errors++;
			break;
		}
	}

	if (rcount < 0) {
		fprintf(stderr, "%s: %s: read error: %s\n",
			myname, file, strerror(errno));
		errors++;
	}

	if (fd != 0) {
		if (close(fd) < 0) {
			fprintf(stderr, "%s: %s: close error: %s\n",
				myname, file, strerror(errno));
			errors++;
		}
	}

	return (errors != 0);
}

int main(int argc, char *argv[])
{
	int i;
	int errs = 0;

	myname = argv[0];

	if (argc == 1)
		errs = process("-");
	else
		for (i = 1; i < argc; i++)
			errs += process(argv[i]);

	return (errs != 0);
}
