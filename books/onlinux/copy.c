#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char buffer[2048];
int version = 1;

int copy(int old, int new)
{
	int count;

	while ((count = read(old, buffer, sizeof(buffer))) > 0)
		(void)write(new, buffer, count);

	return 0;
}

int main(int argc, char *argv[])
{
	int fdold, fdnew;

	if (argc != 3) {
		printf("need 2 arguments for copy program\n");
		exit(1);
	}

	fdold = open(argv[1], O_RDONLY); /* open source file read only */
	if (fdold == -1) {
		printf("cannot open file %s\n", argv[1]);
		exit(1);
	}

	fdnew = creat(argv[2], 0666); /* create target file rw for all */
	if (fdnew == -1) {
		printf("cannot create file %s\n", argv[2]);
		exit(2);
	}

	(void)copy(fdold, fdnew);

	exit(0);
}
