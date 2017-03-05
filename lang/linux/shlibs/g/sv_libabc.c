/*
 * LICENSE: GPL
 *
 * sv_libabc.c
 */
#include <stdio.h>

void abc(void)
{
	void xyz(void);

	printf("abc() calling xyz()\n");
	xyz();
}

__asm__(".symver xyz,xyz@VER_1");
