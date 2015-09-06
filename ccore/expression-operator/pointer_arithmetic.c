#include <stdio.h>
#include <stddef.h>

int main(void)
{
    double dArr[5] = { 0.0, 1.1, 2.2, 3.3, 4.4 };
    double *dPtr = dArr;
    ptrdiff_t i = 0;

    dPtr = dPtr + 1; // dArr[1]
    dPtr = 2 + dPtr; // dArr[3]

    printf("%.1f\n", *dPtr);
    printf("%.1f\n", *(dPtr-1));

    i = dPtr - dArr;
    printf("Pointer point to %dth element of array.\n", i);

    return 0;
}

/*

   dArr

   |
   \|/

   0.0       1.1      2.2    3.3    4.4

   /|\       /|\      /|\
   |   +1    |   +2   |
   ---->    ----->
   dPtr

 */
