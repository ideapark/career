// StrType4.cpp -- line input

#include <iostream>
#include <string>   // make string class available
#include <cstring>  // C-style string library

int main(void)
{
    using namespace std;

    char ChArr[20];
    string Str;

    cout << "Length of string in ChArr before input: "
         << strlen(ChArr) << endl;
    cout << "Length of string in Str before input: "
         << Str.size() << endl;
    
    cout << "Enter a line of text:\n";
    cin.getline(ChArr, 20); // indicate maximum length
    cout << "You entered: " << ChArr << endl;
    
    cout << "Enter another line of text:\n";
    getline(cin, Str);      // cin now an argument; no length specifier
    cout << "You entered: " << Str << endl;
    
    cout << "Length of string in ChArr after input: "
         << strlen(ChArr) << endl;
    cout << "Length of string in Str after input: "
         << Str.size() << endl;

    return 0;
}
