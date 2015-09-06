// FltAdd.cpp -- precision problems with float

#include <iostream>

int main(void)
{
    using namespace std;

    float A = 2.34E+22f;
    float B = A + 1.0f;

    cout << "A = " << A << endl;
    cout << "B - A = " << B - A << endl;

    return 0;
}
