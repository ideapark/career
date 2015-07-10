// FirstRef.cpp -- defining and using a reference

#include <iostream>

int main(void)
{
    using namespace std;
    int Rats = 101;
    int &Rodents = Rats; // rodent is a reference
    cout << "rats = " << Rats;
    cout << ", rodents = " << Rodents << endl;
    Rodents++;
    cout << "rats = " << Rats;
    cout << ", rodents = " << Rodents << endl;
    // some implementations require type casting the following
    // addresses to type unsigned
    cout << "rats address = " << &Rats;
    cout << ", rodents address = " << &Rodents << endl;
    return 0;
}
