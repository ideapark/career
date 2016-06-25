/*
 * Copyright (c) 2014 - 2015, Zhou Peng
 *        ALL RIGHTS RESERVED
 */

#include <string.h>
#include "../include/kiss.h"

static void do_shrink(char *str, int mlen, int rlen)
{
	int i;

	i = -1;
	do {
		i++;
		*(str+rlen+i) = *(str+mlen+i);
	} while (*(str+rlen+i) != '\0');
}

static void do_stretch(char *str, int mlen, int rlen)
{
	int i;

	for (i = 0; *(str+mlen+i) != '\0'; i++)
		;

	do {
		--i;
		*(str+rlen+i) = *(str+mlen+i);
	} while (i > 0);
}

int sed(char *str, const char *match, const char *replace)
{
	int i, off, nsed;
	int mlen, rlen;
	struct range r;

	off = nsed = 0;
	mlen = strlen(match);
	rlen = strlen(replace);

	while (grep(str+off, match, &r)) {
		if (mlen > rlen)
			do_shrink(str+off+r.begin, mlen, rlen);

		if (mlen < rlen)
			do_stretch(str+off+r.begin, mlen, rlen);

		r.end -= (mlen-rlen); /* new range end */

		for (i = r.begin; i < r.end; i++)
			*(str+off+i) = *(replace+i-r.begin);

		off += rlen;
		nsed++;
	}

	return nsed;
}
