#include <stdio.h>

int main(void)
{
    long count;
    const long CYCLES = 5000;
    char readback[1024];
    FILE *fp = fopen("putchar.c", "r");

    if (fp == NULL) {
        fprintf(stderr, "Couldn't open file to read.\n");
        return -1;
    }

    for (count = 0; count <= CYCLES; ++count) {
        printf("\rPerformed %li file reads.", count);
        rewind(fp);
        fgets(readback, 1024, fp);

        if (count%100 != 0)
            continue;
        putchar('\n');
    }
    puts("Done.");

    return 0;
}
