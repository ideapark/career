// ForStr2.cpp -- reversing an array

#include <iostream>
#include <string>

int main(void)
{
    using namespace std;

    cout << "Enter a word: ";
    string Word;
    cin >> Word;

    // physically modify string object
    char Temp;
    int I, J;
    for (J = 0, I = Word.size()-1; J < I; --I, ++J) { // start block
        Temp = Word[I];
        Word[I] = Word[J];
        Word[J] = Temp;
    }                                                 // end block
    cout << Word << "\nDone\n";

    return 0;
}
