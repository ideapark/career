/*
 * implicit convert
 */
#include <stdio.h>

int main(void)
{
    if (-1 < 0u)
        printf("-1 < 0u\n");
    else
        printf("oop, sounds crazy: -1 >= 0u\n");

    return 0;
}
