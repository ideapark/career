#include <stdio.h>

/*
 * printArray: format output to stdio
 * array: float array
 * n: array length
 * ret: void
 */
static void printArray(const float array[], int n)
{
    for (int i = 0; i < n; ++i) {
        printf("%12.2f", array[i]);
        if (i % 5 == 4)
            putchar('\n');
    }
    if (n % 5 != 0)
        putchar('\n');
}

int main(void)
{
    float farray[123];
    printArray(farray, 123);
    return 0;
}
