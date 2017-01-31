#include <stdio.h>

int test_func(char *s)
{
        if (s == NULL) {
                fprintf(stderr, "%s: received null pointer argument\n", __func__);
                return -1;
        }
        /* ... */
        return 0;
}

int main()
{
        test_func(NULL);
        return 0;
}
