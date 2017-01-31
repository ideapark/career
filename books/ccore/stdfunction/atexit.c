#include <stdlib.h>
#include <stdio.h>

int main(void)
{
        void f1(void), f2(void);
        printf("Registering the \"at-exit\" functions f1 and f2:");
        if (atexit(f1) || atexit(f2))
                printf(" falied.\n");
        else
                printf(" done.\n");
        printf("Exiting now.\n");
        exit(0); // equal to 'return 0'
}

void f1(void) { printf("Running the \"at-exit\" function f1().\n"); }
void f2(void) { printf("Running the \"at-exit\" function f2().\n"); }
