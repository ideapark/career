#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int strptrcmp(const void *sp1, const void *sp2);

int main(void)
{
	char *words[] = {
		"Then", "he", "shouted", "What", "I",
		"didn't", "hear", "what", "you", "said"
	};
	int n = sizeof(words)/sizeof(char*);

	qsort(words, n, sizeof(char*), strptrcmp);
	for (int j = 0; j < n; j++)
		puts(words[j]);

	return 0;
}

int strptrcmp(const void *sp1, const void *sp2)
{
	const char *s1 = *(char**)sp1;
	const char *s2 = *(char**)sp2;
	return strcmp(s1, s2);
}
