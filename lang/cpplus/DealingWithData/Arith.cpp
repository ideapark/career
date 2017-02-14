// Arith.cpp -- some C++ arithmetic

#include <iostream>

int main()
{
    using namespace std;

    float Hats, Heads;

    cout.setf(ios_base::fixed, ios_base::floatfield); // fixed-point
    cout << "Enter a number: ";
    cin >> Hats;
    cout << "Enter a another number: ";
    cin >> Heads;

    cout << "Hats = " << Hats << "; Heads = " << Heads << endl;
    cout << "Hats + Heads = " << Hats + Heads << endl;
    cout << "Hats - Heads = " << Hats - Heads << endl;
    cout << "Hats * Heads = " << Hats * Heads << endl;
    cout << "Hats / Heads = " << Hats / Heads << endl;

    return 0;
}
