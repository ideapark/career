// PlusOne.cpp -- the increment operator

#include <iostream>

int main(void)
{
    using std::cout;

    int A = 20;
    int B = 20;

    cout << "a   = " << A << ":   b = " << B << "\n";
    cout << "a++ = " << A++ << ": ++b = " << ++B << "\n";
    cout << "a   = " << A << ":   b = " << B << "\n";

    return 0;
}
