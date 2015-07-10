/*
 * Copyright (C) 2014 - 2015, Zhou Peng
 *        ALL RIGHTS RESERVED
 */

#include "../include/kiss.h"

int uniq(char *str)
{
    int start, next, cnt;

    start = cnt = 0;
    next = 1;

    sort(str);

    while (str[start] != '\0') {
        if (str[start] == str[next])
            cnt++;
        else
            str[++start] = str[next];
        next++;
    }

    return cnt;
}
