// TextIn1.cpp -- reading chars with a while loop

#include <iostream>

int main(void)
{
    using namespace std;

    char Ch;
    int Count = 0;      // use basic input
    cout << "Enter character; enter # to quit:\n";
    cin >> Ch;          // get a character
    while (Ch != '#') { // test the character
        cout << Ch;     // echo the character
        ++Count;        // count the character
        cin >> Ch;      // get the next character
    }
    cout << endl << Count << " characters read\n";
    return 0;
}
