// HexOct2.cpp -- display values in hex and octal

#include <iostream>

using namespace std;

int main(void)
{
    using namespace std;

    int Chest = 42;
    int Waist = 42;
    int Inseam = 42;

    cout << "Monsieur cuts a striking figure!" << endl;
    cout << "Chest = " << Chest << " (decimal for 42)" << endl;
    cout << hex; // manipulator for changing number base
    cout << "Waist = " << Waist << " (hexadecimal for 42)" << endl;
    cout << oct; // manipulator for changing number base
    cout << "Inseam = " << Inseam << " (octal for 42)" << endl;

    return 0;
}
