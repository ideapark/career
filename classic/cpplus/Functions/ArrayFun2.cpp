// ArrayFun2.cpp -- functions with an array argument

#include <iostream>

const int ARRAY_SIZE = 8;

int SumArray(int Array[], int N);

// use std:: instead of using directive
int main(void)
{
    int Cookies[ARRAY_SIZE] = { 1, 2, 4, 8, 16, 32, 64, 128 };
    // some systems require preceding int with static to
    // enable array initiaization
    std::cout << Cookies << " = array address, ";
    // some systems require a type cast: unsigned (Cookies)
    std::cout << sizeof Cookies << " = sizeof cookies\n";
    int Sum = SumArray(Cookies, ARRAY_SIZE);
    std::cout << "Total cookies eaten: " << Sum << "\n";
    Sum = SumArray(Cookies, 3);   // a lie
    std::cout << "First three eaters ate " << Sum << " cookies.\n";
    Sum = SumArray(Cookies+4, 4); // another lie
    std::cout << "Last four eaters ate " << Sum << " cookies.\n";
    return 0;
}

// return the sum of an integer array
int SumArray(int Array[], int N)
{
    int Total = 0;
    std::cout << Array << " = arr, ";
    // some system require a type cast: unsigned (Array)
    std::cout << sizeof Array << " = sizeof arr\n";
    for (int I = 0; I < N; I++)
        Total = Total + Array[I];
    return Total;
}
