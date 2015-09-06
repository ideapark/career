/*
 * calculate.c
 */
#include <math.h>
#include <setjmp.h>
#include <errno.h>

#include "calc.h"

extern jmp_buf jmp_dest; /* longjmp() destination */

double calculate1(double x)
{
    if (x < 0)
        longjmp(jmp_dest, EDOM); /* domain error */
    else
        return sqrt(x);
}

double calculate2(double x)
{
    double y = exp(x);
    if (y == HUGE_VAL)
        longjmp(jmp_dest, ERANGE); /* range error */
    else
        return y;
}
