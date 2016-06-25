/*
 * Copyright (c) 2014 - 2015, Zhou Peng
 *        ALL RIGHTS RESERVED
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../include/kiss.h"

int main(int argc, char *argv[])
{
	char src1[] = "9876543210ZYXWVUTSRQPONMLKJIHGFEDCBA";
	char expect1[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	char src2[] = "";
	char expect2[] = "";

	char src3[] = "qwertyuiop";
	char expect3[] = "eiopqrtuwy";

	sort(src1);
	assert(0 == strcmp(src1, expect1));
	printf("[1] test sort ok.\n");

	sort(src2);
	assert(0 == strcmp(src2, expect2));
	printf("[2] test sort ok.\n");

	sort(src3);
	assert(0 == strcmp(src3, expect3));
	printf("[3] test sort ok.\n");

	return 0;
}
