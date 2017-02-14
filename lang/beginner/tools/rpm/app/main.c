/* main.c */
#include <stdlib.h>
#include "a.h"

extern void function_two();
extern void function_three();

int main(void)
{
    function_two();
    function_three();
    return 0;
}
