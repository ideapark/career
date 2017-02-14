#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
#define MAX_STRING 80
	char name[MAX_STRING];
	char locale[MAX_STRING];
	char *newlocale;
	int i;

	printf("Who are you? ");
	fgets(name, sizeof(name), stdin);

	printf("What is your locale? ");
	fgets(locale, sizeof(locale), stdin);

	name[strlen(name)-1] = '\0'; /* discard '\n' */
	locale[strlen(locale)-1] = '\0';

	newlocale = setlocale(LC_CTYPE, locale);
	if (newlocale == NULL)
		printf("Sorry, couldn't change the locale to %s.\n"
				"The current locale is %s.", locale, setlocale(LC_CTYPE, NULL));
	else
		printf("The new locale is %s. ", newlocale);

	name[0] = toupper(name[0]); /* uppercase the first char */

	i = 1;
	if (isupper(name[i])) { /* the second char is uppercase? */
		while (name[i] != '\0') { /* if so, lowercase the reset chars of name */
			name[i] = tolower(name[i]);
			++i;
		}
	}
	printf("Hello there, %s!\n", name);

	return 0;
}
