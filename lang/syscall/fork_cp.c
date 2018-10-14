#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	/* assume 2 args: source file and target file */
	if (fork() == 0)
		execl("/usr/bin/cp", "cp", argv[1], argv[2], (char *)0);
	wait((int *)0);

	printf("copy done\n");
	return 0;
}
