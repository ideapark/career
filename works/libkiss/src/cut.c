/*
 * Copyright (c) 2014 - 2015, Zhou Peng
 *        ALL RIGHTS RESERVED
 */

#include "../include/kiss.h"

int cut(char *str, const char *cut)
{
	int ncut;
	struct range range;

	ncut = 0;
	while (grep(str, cut, &range)) {
		ncut++;
		do {
			str[range.begin] = str[range.end];
			range.begin++;
			range.end++;
		} while (str[range.begin] != '\0');
	}

	return ncut;
}
