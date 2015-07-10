// strin.cpp -- formatted reading from a char array

#include <string>
#include <sstream>
#include <iostream>

int main(void)
{
    using namespace std;
    string lit = "It was dark and stormy day, and "
                 " the full moon glowed brilliantly. ";
    istringstream instr(lit); // use buf for input
    string word;
    while (instr >> word) // read a word a time
        cout << word << endl;
    return 0;
}
