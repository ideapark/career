// NumStr.cpp -- following number input with line input

#include <iostream>

int main(void)
{
    using namespace std;
    cout << "What year was your house built?\n";
    int Year;
    (cin >> Year).get(); // fix to read and discard the 
                         // newline before reading the address
    cout << "What is its street address?\n";
    char Address[80];
    cin.getline(Address, 80);
    cout << "Year built: " << Year << endl;
    cout << "Address: " << Address << endl;
    cout << "Done!\n";

    return 0;
}
