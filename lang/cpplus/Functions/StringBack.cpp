// StringBack.cpp -- a function that returns a pointer to char

#include <iostream>

char *BuildString(char C, int N); // prototype

int main(void)
{
    using namespace std;

    int Times;
    char Ch;
    cout << "Enter a character: ";
    cin >> Ch;
    cout << "Enter an integer: ";
    cin >> Times;
    char *Ps = BuildString(Ch, Times);
    cout << Ps << endl;
    delete [] Ps;               // free memory
    Ps = BuildString('+', 20);  // reuse pointer
    cout << Ps << "-DONE-" << Ps << endl;
    delete [] Ps;               // free memory

    return 0;
}

// builds string made of n c characters
char* BuildString(char C, int N)
{
    char *PStr = new char[N+1];
    PStr[N] = '\0';  // terminate string
    while (N-- > 0)
        PStr[N] = C; // fill rest of string
    return PStr;
}
