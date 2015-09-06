// CompStr1.cpp -- comparing strings using arrays

#include <iostream>
#include <cstring>  // prototype for strcmp()

int main(void)
{
    using namespace std;

    char Word[5] = "?ate";
    for (char Ch = 'a'; 0 != strcmp(Word, "mate"); Ch++) {
        cout << Word << endl;
        Word[0] = Ch;
    }
    cout << "After loop ends, word is " << Word << endl;

    return 0;
}
