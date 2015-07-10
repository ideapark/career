// Static.cpp -- using a static local variable

#include <iostream>

// constants
const int ArSize = 10;

// function prototype
void StrCount(const char *Str);

int main(void)
{
    using namespace std;
    char Input[ArSize];
    char Next;
    cout << "Enter a line:\n";
    cin.get(Input, ArSize);
    while (cin) {
        cin.get(Next);
        while (Next != '\n') // string didn't fit!
            cin.get(Next);   // dispose of remainder
        StrCount(Input);
        cout << "Enter next line (empty line to quit):\n";
        cin.get(Input, ArSize);
    }
    cout << "Bye\n";
    return 0;
}

void StrCount(const char *Str)
{
    using namespace std;
    static int Total = 0; // staitc local variable
    int Count = 0;        // automatic local variable
    cout << "\"" << Str << "\" contains ";
    while (*Str++) // go to end of string
        Count++;
    Total += Count;
    cout << Count << " characters\n";
    cout << Total << " characters total\n";
}
