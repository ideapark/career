inline void swapf(float *p1, float *p2)
{
        float tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
}

void selection_sortf(float a[], int n)
{
        if (n <= 1) return;
        register float *last = a+n-1, *p, *minPtr;
        for ( ; a < last; ++a) {
                minPtr = a;
                for (p = a+1; p <= last; ++p)
                        if (*p < *minPtr)
                                minPtr = p;
                swapf(a, minPtr);
        }
}

int main(void)
{
        float a[] = { 2, 1, 3, 1, 4, 1, 5, 1 };
        selection_sortf(a, sizeof(a)/sizeof(a[0]));
        return 0;
}
