#include <ctype.h>
#include <stdio.h>

/* test program for isprint bug */
int main(void)
{
    int c;
    while (isprint(c = getchar()) || c != EOF)
        printf("%c", c);
    return 0;
}
