// SecRef.cpp -- defining and using a reference

#include <iostream>

int main(void)
{
    using namespace std;
    int Rats = 101;
    int &Rodents = Rats; // rodent is a reference
    cout << "rats = " << Rats;
    cout << ", Rodents = " << Rodents << endl;
    cout << "rats address = " << &Rats;
    cout << ", rodent address = " << &Rodents << endl;

    int Bunnies = 50;
    Rodents = Bunnies; // can we change the reference?
    cout << "bunnies = " << Bunnies;
    cout << ", rats = " << Rats;
    cout << ", rodents = " << Rodents << endl;
    cout << "bunnies address = " << &Bunnies;
    cout << ", rodents address = " << &Rodents << endl;

    return 0;
}
