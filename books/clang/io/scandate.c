#include <stdio.h>

#define MAXLINE 100
#define MAXNAME 20

int _getline(char s[], int lim)
{
    int c, i;

    i = 0;
    while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

main()
{
    char line[MAXLINE];
    char monthname[MAXNAME];
    int year, month, day;

    while (_getline(line, sizeof(line)) > 0) {
        if (sscanf(line, "%d %s %d", &day, monthname, &year) == 3)
            printf("valid: %s\n", line); /* 25 Dec 1988 */
        else if (sscanf(line, "%d/%d/%d", &month, &day, &year) == 3)
            printf("valid: %s\n", line); /* mm/dd/yyyy */
        else
            printf("invalid: %s\n", line);
    }
    return 0;
}
