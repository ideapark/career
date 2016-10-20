#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void handler(int sig)
{
	static int beeps = 0;

	printf("BEEP\n");
	if (++beeps < 5)
		alarm(1);  /* Next SIGALRM will be delivered in 1 second */
	else {
		printf("BOOM!\n");
		exit(0);
	}
}

int main(void)
{
	signal(SIGALRM, handler);  /* Install SIGALRM handler */
	alarm(1);

	while (1)
		NULL;
	return 0;
}
