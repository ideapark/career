#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void)
{
	int fd;
	struct stat sbuf;

	fd = open(".", O_RDONLY);
	fstat(fd, &sbuf);
	chdir("..");
	fchmod(fd, 0);

	if (fchdir(fd) < 0)
		perror("fchdir back");
	fchmod(fd, sbuf.st_mode & 07777);
	close(fd);

	return 0;
}
