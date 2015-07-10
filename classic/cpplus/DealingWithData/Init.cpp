// Init.cpp -- type changes on initialization

#include <iostream>

int main(void)
{
    using namespace std;

    cout.setf(ios_base::fixed, ios_base::floatfield);
    float Tree = 3;    // int converted to float
    int Guess(3.9832); // double converted to int
    int Debt = 7.2E12; // result not defined in C++
    cout << "Tree = " << Tree << endl;
    cout << "Guess = " << Guess << endl;
    cout << "Debt = " << Debt << endl;

    return 0;
}
