// CCTYPES.cpp -- using the ctype.h library

#include <iostream>
#include <cctype>   // prototypes for character functions

int main(void)
{
    using namespace std;

    cout << "Enter text for analysis, and type @"
            " to terminate input.\n";
    char Ch;
    int WhiteSpace = 0;
    int Digits = 0;
    int Chars = 0;
    int Punct = 0;
    int Others = 0;

    cin.get(Ch);
    while (Ch != '@') {       // test for sentinel
        if (isalpha(Ch))      // is it an alphabetic character?
            Chars++;
        else if (isspace(Ch)) // is it a whitespace character?
            WhiteSpace++;
        else if (isdigit(Ch)) // is it a digit?
            Digits++;
        else if (ispunct(Ch)) // is it punctuation?
            Punct++;
        else
            Others++;
        cin.get(Ch);          // get next character
    }

    cout << Chars << " leters, "
         << WhiteSpace << " whitespace, "
         << Digits << " digits, "
         << Punct << " punctuations, "
         << Others << " others.\n";

    return 0;
}
