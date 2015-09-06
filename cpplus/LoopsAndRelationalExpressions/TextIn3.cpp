// TextIn3.cpp -- reading chars to end of file

#include <iostream>

int main(void)
{
    using namespace std;

    char Ch;
    int Count = 0;
    cin.get(Ch);     // attempt to read a char
    while (cin.fail() == false) { // test for EOF
        cout << Ch;  // echo character
        ++Count;
        cin.get(Ch); // attempt to read another char
    }
    cout << endl << Count << " characters read.\n";
    return 0;
}
