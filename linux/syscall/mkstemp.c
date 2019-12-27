/*
 * Demonstrates mkstemp().
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

int main(void)
{
	static char template[] = "/tmp/myfileXXXXXX";
	char fname[PATH_MAX];
	static char mesg[] = "Here's lookin' at you, kid!\n";
	int fd;
	char buf[BUFSIZ];
	int n;

	strcpy(fname, template);	/* copy template */
	fd = mkstemp(fname);	/* create and open temp file */
	printf("Filename is %s\n", fname);	/* print it for information */

	write(fd, mesg, strlen(mesg));	/* write something to file */

	lseek(fd, 0L, SEEK_SET);	/* rewind to front */
	n = read(fd, buf, sizeof(buf));	/* read data back: NOT '\0' terminated! */
	printf("Got back: %.*s", n, buf);	/* print it out for verification */

	close(fd);		/* close file */
	unlink(fname);		/* remove it */

	return 0;
}
