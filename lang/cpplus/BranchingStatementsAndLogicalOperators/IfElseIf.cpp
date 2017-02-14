// IfElseIf.cpp -- using if else if else

#include <iostream>

const int Fave = 27;

int main(void)
{
    using namespace std;

    int N;
    cout << "Enter a number in the range 1-100 to find ";
    cout << "my favorite number: ";
    do {
        cin >> N;
        if (N < Fave)
            cout << "Too low -- guess again: ";
        else if (N > Fave)
            cout << "Too high -- guess again: ";
        else
            cout << Fave << " is right!\n";
    } while (N != Fave);

    return 0;
}
