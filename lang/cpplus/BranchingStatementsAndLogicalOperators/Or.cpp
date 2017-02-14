// Or.cpp -- using the logical OR operator

#include <iostream>

int main(void)
{
    using namespace std;

    cout << "This program may reformat your hard disk\n"
            "and destroy all your data.\n"
            "Do you wish to continue? <y/n> ";
    char Ch;
    cin >> Ch;

    if (Ch == 'y' || Ch == 'Y')      // y or Y
        cout << "You were warned!\a\a\n";
    else if (Ch == 'n' || Ch == 'N') // n or N
        cout << "A wise choice ... bye\n";
    else
        cout << "That wasn't a y or n! Apparently you "
                "can't follow\ninstructions, so "
                "I'll trash your disk anyway.\a\a\a\n";

    return 0;
}
