// TextIn2.cpp -- using cin.get(char)

#include <iostream>

int main(void)
{
    using namespace std;

    char Ch;
    int Count = 0;
    cout << "Enter characters; enter # to quit:\n";
    cin.get(Ch);        // use the cin.get(ch) function
    while (Ch != '#') {
        cout << Ch;
        ++Count;
        cin.get(Ch);    // use it again
    }
    cout << endl << Count << " characters read\n";
    return 0;
}
