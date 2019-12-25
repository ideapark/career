#include <string.h>
#include <stdio.h>

int main(void)
{
	int result = 0;
	char word1[256];
	char word2[256];
	char *greaterlessequal;

	while (result < 2) {
		puts("Type two words, please.");
		result = scanf("%s%s", word1, word2);
	}

	result = strcmp(word1, word2);

	if (result < 0)
		greaterlessequal = "less than";
	else if (result > 0)
		greaterlessequal = "greater than";
	else
		greaterlessequal = "the same as";
	printf("The word \"%s\" is %s the word \"%s\".\n",
	       word1, greaterlessequal, word2);

	return 0;
}
