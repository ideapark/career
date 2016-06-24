/*
 * Copyright (C) 2014 - 2015, Zhou Peng
 *        ALL RIGHTS RESERVED
 */

#include <stdio.h>
#include <assert.h>
#include "../include/kiss.h"

int main(int argc, char *argv[])
{

    char src1[] = "abcdefghijklmn";
    char pat1[] = "efgh";
    struct range range1;

    char src2[] = "abcdefghijklmn";
    char pat2[] = "efxgh";
    struct range range2;

    char src3[] = "abcdefghijklmn";
    char pat3[] = "";
    struct range range3;

    assert(true == grep(src1, pat1, &range1));
    assert(4 == range1.begin);
    assert(8 == range1.end);
    printf("[1] test grep ok.\n");

    assert(false == grep(src2, pat2, &range2));
    assert(0 == range2.begin);
    assert(0 == range2.end);
    printf("[2] test grep ok.\n");

    assert(false == grep(src3, pat3, &range3));
    assert(0 == range3.begin);
    assert(0 == range3.end);
    printf("[3] test grep ok.\n");

    return 0;
}
