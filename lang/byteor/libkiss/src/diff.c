/*
 * Copyright (c) 2014 - 2015, Zhou Peng <p@ctriple.cn>
 *        ALL RIGHTS RESERVED
 */

#include "../include/kiss.h"

int diff(const char *str1, const char *str2)
{
	int dcnt;
	int i, j;

	dcnt = i = j = 0;

	while (str1[i] != '\0' && str2[j] != '\0') {
		if (str1[i] != str2[j])
			dcnt++;
		i++;
		j++;
	}

	while (str1[i] != '\0') {
		dcnt++;
		i++;
	}

	while (str2[j] != '\0') {
		dcnt++;
		j++;
	}

	return dcnt;
}
