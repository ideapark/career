/*
 * LICENSE: GPL
 *
 * sv_prog_complex.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//void xxx(void) { printf("Hi there\n"); }

int main(int argc, char *argv[])
{
	void xyz(void);
	void xyz_old(void), xyz_new(void);
	void abc(void);

	printf("Calling abc()\n");
	abc();

	printf("Calling xyz()\n");
	xyz();

	printf("Calling xyz_new()\n");
	xyz_new();

	printf("Calling xyz_old()\n");
	xyz_old();

	//xxx();

	exit(0);
}
//__asm__(".symver xyz_old,xyz@VER_1");
