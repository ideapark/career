// Bondini.cpp -- using escape sequences

#include <iostream>

int main(void)
{
    using namespace std;

    cout << "\aOperation \"HyperHype\" is now activated!\n";
    cout << "Enter your agent code:________\b\b\b\b\b\b\b\b";
    long Code;
    cin >> Code;
    cout << "\aYou entered " << Code << "...\n";
    cout << "\aCode verified! Proceed with Plan Z3!\n";

    return 0;
}
