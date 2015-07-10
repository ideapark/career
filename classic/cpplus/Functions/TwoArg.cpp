// TwoArg.cpp -- a function with 2 arguments

#include <iostream>

using namespace std;

void NChars(char, int);

int main(void)
{
    int Times;
    char Ch;
    cout << "Enter a character: ";
    cin >> Ch;
    while (Ch != 'q') { // q to quit
        cout << "Enter an integer: ";
        cin >> Times;
        NChars(Ch, Times); // function with two arguments
        cout << "\nEnter another character or press the"
                " q-key to quit: ";
        cin >> Ch;
    }
    cout << "The value of times is " << Times << ".\n";
    cout << "Bye\n";
    return 0;
}

void NChars(char C, int N) // display c n times
{
    while (N-- > 0) // continue until n reaches 0
        cout << C;
}
