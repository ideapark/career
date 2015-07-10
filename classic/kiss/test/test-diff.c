/*
 * Copyright (C) 2014 - 2015, Zhou Peng
 *        ALL RIGHTS RESERVED
 */

#include <stdio.h>
#include <assert.h>
#include "../include/kiss.h"

int main(int argc, char *argv[])
{
    char src1[] = "acegi";
    char src2[] = "bdfhj";

    char src3[] = "";
    char src4[] = "bdfhj";

    char src5[] = "acegi";
    char src6[] = "adehi";

    assert(5 == diff(src1, src2));
    printf("[1] test diff ok.\n");

    assert(5 == diff(src3, src4));
    printf("[2] test diff ok.\n");

    assert(2 == diff(src5, src6));
    printf("[3] test diff ok.\n");

    return 0;
}
