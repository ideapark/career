#include <signal.h>
#include <string.h>
#include <unistd.h>

void handler(int signum)
{
	char buf[200], *cp;
	int offset;

	/* jump through hoops to avoid fprintf() */
	strcpy(buf, "handler: caught signal ");
	cp = buf + strlen(buf);	/* cp points at terminating '\0' */

	if (signum > 100)	/* unlikely */
		offset = 3;
	else if (signum > 10)
		offset = 2;
	else
		offset = 1;

	cp += offset;
	*cp-- = '\0';		/* terminating string */

	while (signum > 0) {	/* work backwards, filling in digits */
		*cp-- = (signum % 10) + '0';
		signum /= 10;
	}

	strcat(buf, "\n");
	(void)write(2, buf, strlen(buf));
}

int main(void)
{
	(void)signal(SIGINT, handler);

	for (;;)
		pause();	/* wait for a signal */

	return 0;
}
