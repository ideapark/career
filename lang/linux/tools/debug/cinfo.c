/*
 * gcc -Wall -pedantic -ansi -DDEBUG cinfo.c
 */

#include <stdio.h>

int main(void)
{
#ifdef DEBUG
        printf("Compiled: "__DATE__" at "__TIME__"\n");
        printf("This is line %d of file %s\n", __LINE__, __FILE__);
#endif
        printf("Hello world\n");
        return 0;
}
