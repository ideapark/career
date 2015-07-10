// Left.cpp -- string function with a default argument

#include <iostream>

const int ARRAY_SIZE = 80;

char* Left(const char *Str, int N = 1);

int main(void)
{
    using namespace std;
    char Sample[ARRAY_SIZE];
    cout << "Enter a string:\n";
    cin.get(Sample, ARRAY_SIZE);
    char *PS = Left(Sample, 4);
    cout << PS << endl;
    delete [] PS; // free old string
    PS = Left(Sample);
    cout << PS << endl;
    delete [] PS; // free old string
    return 0;
}

// this function returns a pointer to a new string
// consisting of the first n characters in the str string.
char* Left(const char *Str, int N)
{
    if (N < 0) N = 0;
    char *P = new char[N+1];
    int I;
    for (I = 0; I < N && Str[I]; I++)
        P[I] = Str[I]; // copy characters
    while (I <= N)
        P[I++] = '\0'; // set rest of string to '\0'
    return P;
}
