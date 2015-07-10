// TypeCast.cpp -- forcing type changes

#include <iostream>

int main(void)
{
    using namespace std;

    int Auks, Bats, Coots;

    // the following statement adds the values as double,
    // then converts the result to int
    Auks = 19.99 + 11.99;

    // these statements add values as int
    Bats = (int) 19.99 + (int) 11.99; // old C syntax
    Coots = int(19.99) + int(11.99);  // new C++ syntax
    cout << "Auks = " << Auks << ", Bats = " << Bats;
    cout << ", Coots = " << Coots << endl;

    char Ch = 'Z';
    cout << "The code for " << Ch << " is "; // print as char
    cout << int(Ch) << endl;                 // print as int
    cout << "Yes, the code is ";
    cout << static_cast<int>(Ch) << endl;    // using static_cast

    return 0;
}
