#include <stddef.h>
#include <stdio.h>

struct belongings {
        char   c;
        short  s;
        int    i;
        float  f;
        double d;
};

int main(void)
{
        printf("offset c: %lu\n", offsetof(struct belongings, c));
        printf("offset s: %lu\n", offsetof(struct belongings, s));
        printf("offset i: %lu\n", offsetof(struct belongings, i));
        printf("offset d: %lu\n", offsetof(struct belongings, d));
        return 0;
}
