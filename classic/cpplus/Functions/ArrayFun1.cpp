// ArrayFun1.cpp -- functions with an array argument

#include <iostream>

const int ARRAY_SIZE = 8;

int SumArray(int Array[], int N); // prototype

int main(void)
{
    using namespace std;
    int Cookies[ARRAY_SIZE] = { 1, 2, 4, 8, 16, 32, 64, 128 };
    // some systems require preceding int with static to
    // enable array initiaization
    int Sum = SumArray(Cookies, ARRAY_SIZE);
    cout << "Total cookies eaten: " << Sum << "\n";
    return 0;
}

// return the sum of an integer array
int SumArray(int Array[], int N)
{
    int Total = 0;
    for (int I = 0; I < N; I++)
        Total = Total + Array[I];
    return Total;
}
