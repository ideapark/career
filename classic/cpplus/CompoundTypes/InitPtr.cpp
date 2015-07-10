// InitPtr.cpp -- initialize a pointer

#include <iostream>

int main(void)
{
    using namespace std;

    int Higgens = 5;
    int *Pt = &Higgens;

    cout << "Value of higgens = " << Higgens
         << "; Address of higgens = " << &Higgens << endl;
    cout << "Value of *pt = " << *Pt
         << "; Value of pt = " << Pt << endl;

    return 0;
}
