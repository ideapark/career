// TextIn4.cpp -- reading chars with cin.get()

#include <iostream>
#include <cstdio> // EOF

int main(void)
{
    using namespace std;
    int Ch; // should be int, not char
    int Count = 0;
    while ((Ch = cin.get()) != EOF) { // test for end-of-file
        cout.put(char(Ch));
        ++Count;
    }
    cout << endl << Count << " characters read.\n";
    return 0;
}
