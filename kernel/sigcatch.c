#include <signal.h>
#include <string.h>
#include <unistd.h>

void handler(int signum)
{
	char buf[200], *cp;
	int offset;

	strcpy(buf, "handler: caught signal ");
	cp = buf + strlen(buf);

	if (signum > 100)	/* unlikely */
		offset = 3;
	else if (signum > 10)
		offset = 2;
	else
		offset = 1;

	cp += offset;
	*cp-- = '\0';

	while (signum > 0) {
		*cp-- = (signum % 10) + '0';
		signum /= 10;
	}

	strcat(buf, "\n");
	write(2, buf, strlen(buf));
}

int main(void)
{
	signal(SIGINT, handler);

	for (;;)
		pause();

	return 0;
}
