#include <stdio.h>

#define MAXLINE  1000     /* maximum line length */

int _getline(char line[], int max);
int strindex(char source[], char searchfor[]);

char pattern[] = "ould";  /* search pattern */

main()
{
    char line[MAXLINE];
    int found = 0;

    while (_getline(line, MAXLINE) > 0) {
        if (strindex(line, pattern) >= 0) {
            printf("%s", line);
            found++;
        }
    }
    return found;
}

int strindex(char s[], char t[])
{
    int i, j, k;

    for (i = 0; s[i] != '\0'; i++) {
        for (j=i, k=0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
}
