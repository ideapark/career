// Not.cpp -- using the not operator

#include <iostream>
#include <climits>

bool IsInt(double);

int main(void)
{
    using namespace std;

    double Num;
    cout << "Yo, dude! Enter an integer value: ";
    cin >> Num;
    while (!IsInt(Num)) { // continue while num is not int-able
        cout << "Out of range -- please try again: ";
        cin >> Num;
    }
    int Val = int(Num);  // type cast
    cout << "You've entered the integer " << Val << "\nBye\n";
    return 0;
}

bool IsInt(double X)
{
    if (X <= INT_MAX && X >= INT_MIN) // use climits values
        return true;
    else
        return false;
}
