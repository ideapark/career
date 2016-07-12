/*
 * Boyer-Moore Search
 *
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#include <assert.h>
#include <string.h>

int main(void)
{
	const char *string1 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const char *search1 = "xyzABC";
	const char *search2 = "xyzXYZ";

	char *str1 = boyer_moore(string1, strlen(string1), search1, strlen(search1));
	assert(str1 != NULL && strncmp(str1, search1, strlen(search1)) == 0);

	char *str2 = boyer_moore(string1, strlen(string1), search2, strlen(search2));
	assert(str2 == NULL);

	return 0;
}
