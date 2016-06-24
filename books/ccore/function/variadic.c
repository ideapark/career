#include <stdio.h>
#include <stdarg.h>

/*
 * add(): variadic parameter function
 */
double add(int n, ...)
{
    int i = 0;
    double sum = 0.0;
    va_list argptr;
    va_start(argptr, n);
    for (i = 0; i < n; ++i)
        sum += va_arg(argptr, double);
    va_end(argptr);
    return sum;
}

int main(void)
{
    printf("%5.2f\n", add(2, 3.3, 4.4));
    printf("%5.2f\n", add(3, 3.3, 4.4, 5.5));
    printf("%5.2f\n", add(4, 3.3, 4.4, 5.5, 6.6));
    return 0;
}
