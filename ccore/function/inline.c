#include <stdio.h>

inline void swapf(float *p1, float *p2)
{
    float tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

void selection_sortf(float a[], int n)
{
    register int i, j, mini;
    for (i = 0; i < n-1; ++i) {
        mini = i;
        for (j = i+1; j < n; ++j)
            if (a[j] < a[mini])
                mini = j;
        swapf(a+i, a+mini);
    }
}

int main(void)
{
    float a[] = { 2, 20, 22, 1, 4, 2, 20, 22, 1, 4 };
    printf("before sort: ");
    for (int i = 0; i < sizeof(a)/sizeof(a[0]); ++i)
        printf("%7.2f", a[i]);
    printf("\nafter sort: ");
    selection_sortf(a, sizeof(a)/sizeof(a[0]));
    for (int i = 0; i < sizeof(a)/sizeof(a[0]); ++i)
        printf("%7.2f", a[i]);
    return 0;
}
