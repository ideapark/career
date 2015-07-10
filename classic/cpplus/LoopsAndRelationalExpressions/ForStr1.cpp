// ForStr1.cpp -- using for with a string

#include <iostream>
#include <string>

int main(void)
{
    using namespace std;

    cout << "Enter a word: ";
    string Word;
    cin >> Word;

    // display letters in reverse order
    for (int i = Word.size()-1; i >= 0; i--)
        cout << Word[i];
    cout << "\nBye.\n";

    return 0;
}
