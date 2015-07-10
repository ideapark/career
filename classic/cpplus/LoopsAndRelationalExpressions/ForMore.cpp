// ForMore.cpp -- more looping with for

#include <iostream>

const int ArSize = 16; // example of external declaration

int main(void)
{
    long long Factorials[ArSize];
    Factorials[1] = Factorials[0] = 1LL;
    for (int i = 2; i < ArSize; i++)
        Factorials[i] = i * Factorials[i-1];
    for (int i = 0; i < ArSize; i++)
        std::cout << i << "! = " << Factorials[i] << std::endl;

    return 0;
}
