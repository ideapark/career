// ArrayFunc4.cpp -- functions with an array range

#include <iostream>

const int ARRAY_SIZE = 8;

int SumArray(const int *Begin, const int *End);

int main(void)
{
    using namespace std;

    int Cookies[ARRAY_SIZE] = { 1, 2, 4, 8, 16, 32, 64, 128 };
    // some systems require preceding int with static to
    // eanble array initialization
    int Sum = SumArray(Cookies, Cookies+ARRAY_SIZE);
    cout << "Total cookies eaten: " << Sum << endl;
    Sum = SumArray(Cookies, Cookies+3);   // first 3 elements
    cout << "First three eaters ate " << Sum << " cookies.\n";
    Sum = SumArray(Cookies+4, Cookies+8); // last 4 elements
    cout << "Last four eaters ate " << Sum << " cookies.\n";
    return 0;
}

// return the sum of an integer array
int SumArray(const int *Begin, const int *End)
{
    const int *Pt;
    int Total = 0;
    for (Pt = Begin; Pt != End; Pt++) {
        Total = Total + *Pt;
    }
    return Total;
}
