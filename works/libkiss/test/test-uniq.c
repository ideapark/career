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
    char src1[] = "1111111111";
    char expect1[] = "1";

    char src2[] = "1212121212";
    char expect2[] = "12";

    char src3[] = "";
    char expect3[] = "";

    char src4[] = "ba";
    char expect4[] = "ab";

    assert(9 == uniq(src1));
    assert(0 == strcmp(src1, expect1));
    printf("[1] test uniq ok.\n");

    assert(8 == uniq(src2));
    assert(0 == strcmp(src2, expect2));
    printf("[2] test uniq ok.\n");

    assert(0 == uniq(src3));
    assert(0 == strcmp(src3, expect3));
    printf("[3] test uniq ok.\n");

    assert(0 == uniq(src4));
    assert(0 == strcmp(src4, expect4));
    printf("[4] test uniq ok.\n");

    return 0;
}
