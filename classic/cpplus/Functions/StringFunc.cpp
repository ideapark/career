// StringFunc.cpp -- functions with a string argument

#include <iostream>

unsigned int CInString(const char *Str, char Ch);

int main(void)
{
    using namespace std;

    char Mmm[15] = "minimum"; // string in an array
    // some systems require preceding char with static to
    // enable array initialization
    char *Wail = "ululate";   // wail points to string
    unsigned int Ms = CInString(Mmm, 'm');
    unsigned int Us = CInString(Wail, 'u');
    cout << Ms << " m characters in " << Mmm << endl;
    cout << Us << " u characters in " << Wail << endl;

    return 0;
}

// this function counts the number of ch characters
// in the string str
unsigned int CInString(const char *Str, char Ch)
{
    unsigned int Count = 0;
    while (*Str) { // quit when *str is '\0'
        if (*Str == Ch)
            Count++;
        Str++;     // move pointer to next char
    }
    return Count;
}
