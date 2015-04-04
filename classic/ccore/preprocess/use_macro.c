#include "macro.h"

int main(void)
{
    puts(TITLE);
    static char myBuffer[BUFFER_SIZE];
    // Be carefull with the output
    setvbuf(stdout, myBuffer, _IOFBF, BUFFER_SIZE);

    double data[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; ++i)
        data[i] = 10.0 * RANDOM;
    for (int i = 0; i < ARRAY_SIZE; ++i)
        printf("%010.5f\n", data[i]);

    printLog("%s: intVar = %d\n", __func__, 10);

    return 0;
}
