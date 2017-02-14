#include <stdlib.h>
#include <stdio.h>

int main(void)
{
        char *s = " -135792468.00 Balance on Dec. 31";
        printf("\"%s\", becomes %ld\n", s, atol(s));
        return 0;
}
