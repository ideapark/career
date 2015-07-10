/*
 * Copyright (C) 2014 - 2015, Zhou Peng
 *        ALL RIGHTS RESERVED
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../include/kiss.h"

int main(int argc, char *argv[])
{
    char src1[] = "abcdefghijklmn";
    char cut1[] = "cdef";
    char expect1[] = "abghijklmn";

    char src2[] = "abcdefghijklmn";
    char cut2[] = "";
    char expect2[] = "abcdefghijklmn";

    char src3[] = "";
    char cut3[] = "abcdefghijklmn";
    char expect3[] = "";

    cut(src1, cut1);
    assert(0 == strcmp(src1, expect1));
    printf("[1] test cut ok\n");

    cut(src2, cut2);
    assert(0 == strcmp(src2, expect2));
    printf("[2] test cut ok\n");

    cut(src3, cut3);
    assert(0 == strcmp(src3, expect3));
    printf("[3] test cut ok\n");

    return 0;
}
