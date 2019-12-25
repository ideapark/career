#include <unistd.h>

#define BUFSIZ  8192
#define EOF     (-1)

int getchar(void)
{
	static char buf[BUFSIZ];
	static char *bufp = buf;
	static int n = 0;

	if (n == 0) {
		n = read(0, buf, sizeof buf);
		bufp = buf;
	}
	return (--n >= 0) ? (unsigned char)*bufp++ : EOF;
}
