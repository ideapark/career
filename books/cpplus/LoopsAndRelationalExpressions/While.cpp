// While.cpp -- introducing the while loop

#include <iostream>

const int ArSize = 20;

int main(void)
{
    using namespace std;

    char Name[ArSize];
    cout << "Your first name, please: ";
    cin >> Name;
    cout << "Here is your name, verticalized and ASCIIized:\n";
    int I = 0;                 // start at beginnning of string
    while (Name[I] != '\0') {  // process to end of string
        cout << Name[I] << ": " << int(Name[I]) << endl;
        I++;                   // don't forget this step
    }
    return 0;
}
