/*
 * Copyright (c) 2014 - 2015, Zhou Peng <p@ctriple.cn>
 *        ALL RIGHTS RESERVED
 */

#include "../include/kiss.h"

int cut(char *str, const char *cut)
{
	int ncut;
	struct range r;

	ncut = 0;
	while (grep(str, cut, &r)) {
		ncut++;
		do {
			str[r.begin] = str[r.end];
			r.begin++;
			r.end++;
		} while (str[r.begin] != '\0');
	}

	return ncut;
}
