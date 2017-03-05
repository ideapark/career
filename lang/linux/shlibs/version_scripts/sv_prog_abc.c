/* sv_prog_abc.c */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	void xyz(void), abc(void);

	printf("main() calling xyz()\n");
	xyz();

	abc();

	exit(EXIT_SUCCESS);
}
