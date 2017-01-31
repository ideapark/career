#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

double vproduct(int n, va_list argptr);
double vsum(int n, va_list argptr);
double vop(const char *op, int argcount, ...);

int main(void)
{
        double d1, d2, d3, d4, d5, d6;
        puts("Enter six floating-point numbers, please: ");
        scanf("%lf%lf%lf%lf%lf%lf", &d1, &d2, &d3, &d4, &d5, &d6);

        char *operation[] = {
                "sum",
                "product",
                "product minus the sum",
                NULL
        };

        printf("\nUsing the three numbers %lf, %lf, and %lf.\n", d1, d2, d3);
        for (int i = 0; operation[i] != NULL; i++) {
                printf("The %s of these %d numbers is %lf\n", operation[i], 3,
                       vop(operation[i], 3, d1, d2, d3));
        }

        printf("\nUsing six numbers:\n\t%lf \t%lf \t%lf \n\t%lf \t%lf \t%lf\n",
               d1, d2, d3, d4, d5, d6);
        for (int i = 0; operation[i] != NULL; i++) {
                printf("The %s of these %d numbers is %lf\n", operation[i], 6,
                       vop(operation[i], 6, d1, d2, d3, d4, d5, d6));
        }

        return 0;
}

double vop(const char *op, int argcount, ...)
{
        va_list argptr;
        double result;

        va_start(argptr, argcount);

        if (strcmp(op, "sum") == 0) {
                result = vsum(argcount, argptr);
        } else if (strcmp(op, "product") == 0) {
                result = vproduct(argcount, argptr);
        } else if (strcmp(op, "product minus the sum") == 0) {
                va_list duplicate_argptr; /* clone va_list current status */
                va_copy(duplicate_argptr, argptr);
                result = vproduct(argcount, argptr) - vsum(argcount, duplicate_argptr);
                va_end(duplicate_argptr); /* delete clone */
        } else {
                result = NAN;
        }

        va_end(argptr); /* clear status */
        return result;
}

double vproduct(int n, va_list argptr)
{
        double product = 1.0;
        for (int i = 0; i < n; i++)
                product *= va_arg(argptr, double);
        return product;
}

double vsum(int n, va_list argptr)
{
        double sum = 0.0;
        for (int i = 0; i < n; i++)
                sum += va_arg(argptr, double);
        return sum;
}
