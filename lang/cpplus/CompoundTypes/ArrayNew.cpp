// ArrayNew.cpp -- using the new operator for arrays

#include <iostream>

int main(void)
{
    using namespace std;

    double *P3 = new double[3]; // space for 3 doubles
    P3[0] = 0.2;                // treat P3 like an array name
    P3[1] = 0.5;
    P3[2] = 0.8;
    cout << "p3[1] is " << P3[1] << ".\n";
    P3 = P3 + 1;                // increment the pointer
    cout << "Now p3[0] is " << P3[0] << " and ";
    cout << "pi[1] is " << P3[1] << ".\n";
    P3 = P3 - 1;                // point back to beginning
    delete[] P3;                // free the memory

    return 0;
}
