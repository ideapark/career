#include <iostream>
#include <iomanip>

#define PRINT_SIZEOF(t)         \
do {                            \
    std::cout << std::setw(20)  \
              << #t             \
              << ": "           \
              << sizeof(t)      \
              << std::endl;     \
} while (false)

int main(void)
{
    PRINT_SIZEOF(char);
    PRINT_SIZEOF(signed char);
    PRINT_SIZEOF(unsigned char);

    PRINT_SIZEOF(short);
    PRINT_SIZEOF(signed short);
    PRINT_SIZEOF(unsigned short);

    PRINT_SIZEOF(int);
    PRINT_SIZEOF(signed int);
    PRINT_SIZEOF(unsigned int);

    PRINT_SIZEOF(long);
    PRINT_SIZEOF(signed long);
    PRINT_SIZEOF(unsigned long);

    PRINT_SIZEOF(long long);
    PRINT_SIZEOF(signed long long);
    PRINT_SIZEOF(unsigned long long);

    PRINT_SIZEOF(float);
    PRINT_SIZEOF(double);

    return 0;
}
