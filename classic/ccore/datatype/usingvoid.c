// usingvoid.c -- demonstrate usage of void
// --------------------------------------------------------------------

#include <stdio.h>
#include <time.h>
#include <stdlib.h> // void srand(unsigned int seed);
                    // int rand(void);
                    // void *malloc(size_t size);
                    // void free(void *ptr);
                    // void exit(int status);

enum { ARR_LEN = 100 };

int main(void)
{
    int i,
        *pNumbers = malloc(ARR_LEN * sizeof(int));
    if (pNumbers == NULL) {
        fprintf(stderr, "Insufficient memory.\n");
        exit(1);
    }
    srand((unsigned)time(NULL)); // seed random generator
    for (i = 0; i < ARR_LEN; ++i)
        pNumbers[i] = rand() % 10000; // store random number
    printf("\n%d random numbers between 0 and 9999:\n", ARR_LEN);
    for (i = 0; i < ARR_LEN; ++i) {
        printf("%6d", pNumbers[i]);
        if (i % 10 == 9)
            putchar('\n');
    }
    free(pNumbers);
    return 0;
}
