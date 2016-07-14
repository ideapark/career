#include <stdio.h>
#include <stdlib.h>

void callback1()  {
	printf("callback1 called\n");
}

void callback2()  {
	printf("callback2 called\n");
}

void callback3()  {
	printf("callback3 called\n");
}

int main(int argc, char *argv[])
{
	printf("registering callback1\n");
	atexit(callback1);

	printf("registering callback2\n");
	atexit(callback2);

	printf("registering callback3\n");
	atexit(callback3);

	printf("exiting now\n");
	exit(0);
}
