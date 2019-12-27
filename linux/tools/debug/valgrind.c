/*
 * valgrind memory debug
 *
 * valgrind --leak-check=yes -v a.out
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
        char *ptr = (char *)malloc(1024);
        char ch;

        /* uninitialized read */
        ch = ptr[1024];

        /* write beyond the block */
        ptr[1024] = 0;

        /* orphan the block */
        ptr = 0;

        return 0;
}
