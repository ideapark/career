#include <stdio.h>
#include <string.h>

void func0(void) { puts("This is the function func0(). "); }
void func1(void) { puts("This is the function func1(). "); }

int main(void)
{
    int *iPtr = 0;
    int iArray[] = { 0, 10, 20 };
    int array_length = sizeof(iArray) / sizeof(int);

    printf("The array starts at the address %p.\n", iArray);
    *iArray = 5; // iArray[0] = 5;

    iPtr = iArray + array_length - 1; // iPtr = &iArray[array_length-1];
    printf("The last element of the array is %d.\n", *iPtr);

    char msg[80] = "I'm a string literal.";
    printf("The string is %d characters long.\n", strlen(msg)); // 21
    printf("The array named msg is %d bytes long.\n", sizeof(msg)); // 80

    void (*funcTable[2])(void) = { func0, func1 };
    int i;
    for (i = 0; i < 2; i++)
        funcTable[i]();
    return 0;
}
