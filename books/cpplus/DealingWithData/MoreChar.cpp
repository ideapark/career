// MoreChar.cpp -- the char type and int type contrasted

#include <iostream>

int main(void)
{
    using namespace std;

    char Ch = 'M'; // assign ASCII code for M to Ch
    int I = Ch;    // store same code in an int
    cout << "The ASCII code for " << Ch << " is " << I << endl;

    cout << "Add one to the character code:" << endl;
    Ch = Ch + 1; // change character code in Ch
    I = Ch;      // save new character code in I
    cout << "The ASCII code for " << Ch << " is " << I << endl;

    // using the cout.put() member function to display a char
    cout << "Displaying char Ch using cout.put(Ch): ";
    cout.put(Ch);

    // using cout.put() to display a char constant
    cout.put('!');

    cout << endl << "Done" << endl;

    return 0;
}
