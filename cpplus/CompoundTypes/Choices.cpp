// Choices.cpp -- array variations

#include <iostream>
#include <vector>   // STL C++98
#include <array>    // C++11

int main(void)
{
    using namespace std;

    // C, original C++
    double A1[4] = { 1.2, 2.4, 3.6, 4.8 };

    // C++98 STL
    vector<double> A2(4); // create vector with 4 elements

    // no simple way to initialize in C98
    A2[0] = 1.0/3.0;
    A2[1] = 1.0/5.0;
    A2[2] = 1.0/7.0;
    A2[3] = 1.0/9.0;

    // C++11 -- create and initialize array object
    array<double, 4> A3 = { 3.14, 2.72, 1.62, 1.41 };
    array<double, 4> A4;
    A4 = A3; // valid for array objects of same size

    // use array notation
    cout << "a1[2]: " << A1[2] << "@" << &A1[2] << endl;
    cout << "a2[2]: " << A2[2] << "@" << &A2[2] << endl;
    cout << "a3[2]: " << A3[2] << "@" << &A3[2] << endl;
    cout << "a4[2]: " << A4[2] << "@" << &A4[2] << endl;

    // misdeed
    A1[-2] = 20.2;
    cout << "a1[-2]: " << A1[-2] << "@" << &A1[-2] << endl;
    cout << "a3[2]: " << A3[2] << "@" << &A3[2] << endl;
    cout << "a4[2]: " << A4[2] << "@" << &A4[2] << endl;

    return 0;
}
