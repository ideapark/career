/*
 * produce a core dump
 */
#include <stdio.h>
#include <stdlib.h>

/*
 * build up some functions calls
 */
void recurse(void)
{
    static int i;

    if (++i == 3)
        abort();
    else
        recurse();
}

int main(int argc, char *argv[])
{
    recurse();

    return 0;
}
