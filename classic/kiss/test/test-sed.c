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
    char mat1[] = "efgh";
    char rep1[] = "####";
    char expect1[] = "abcd####ijklmn";
    int nsed1;

    char src2[] = "abcdefghijklmn";
    char mat2[] = "efgh";
    char rep2[] = "";
    char expect2[] = "abcdijklmn";
    int nsed2;

    char src3[] = "abcdefghijklmn";
    char mat3[] = "";
    char rep3[] = "efgh";
    char expect3[] = "abcdefghijklmn";
    int nsed3;

    char src4[27] = "ab#cd#ef#g";
    char mat4[] = "#";
    char rep4[] = "@@@";
    char expect4[] = "ab@@@cd@@@ef@@@g";
    int nsed4;

    nsed1 = sed(src1, mat1, rep1);
    assert(1 == nsed1);
    assert(0 == strcmp(src1, expect1));
    printf("[1] test sed ok.\n");

    nsed2 = sed(src2, mat2, rep2);
    assert(1 == nsed2);
    assert(0 == strcmp(src2, expect2));
    printf("[2] test sed ok.\n");

    nsed3 = sed(src3, mat3, rep3);
    assert(0 == nsed3);
    assert(0 == strcmp(src3, expect3));
    printf("[3] test sed ok.\n");

    nsed4 = sed(src4, mat4, rep4);
    assert(3 == nsed4);
    assert(0 == strcmp(src4, expect4));
    printf("[4] test sed ok.\n");

    return 0;
}
