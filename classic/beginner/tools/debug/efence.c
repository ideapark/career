/*
 * ElectricFence virtual memory debug
 *
 * gcc -Wall efence.c -lefence
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *ptr = (char *)malloc(1024);
    ptr[0] = 0;

    /* write beyond the block */
    ptr[1024] = 0;
    return 0;
}
