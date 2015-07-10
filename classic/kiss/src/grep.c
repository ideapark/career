/*
 * Copyright (C) 2014 - 2015, Zhou Peng
 *        ALL RIGHTS RESERVED
 */

#include <string.h>
#include "../include/kiss.h"

static bool strcmp_n(const char *s1, const char *s2, size_t n)
{
    int i;

    for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++) {
        if (s1[i] == s2[i])
            n--;
        else
            break;
    }

    return ((n > 0) ? false : true);
}

bool grep(const char *str, const char *match, struct range *range)
{
    int len, i;

    range->begin = 0;
    range->end = 0;

    len = strlen(match);

    for (i = 0; str[i] != 0; i++) {
        if (str[i] == match[0]) {
            if (strcmp_n(str+i, match, len)) {
                range->begin = i;
                range->end = i+len;
                return true;
            }
        }
    }

    return false;
}
