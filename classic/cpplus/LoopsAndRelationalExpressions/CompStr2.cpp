// CompStr2.cpp -- comparing strings using arrays

#include <iostream>
#include <string>   // string class

int main(void)
{
    using namespace std;

    string Word = "?ate";
    for (char Ch = 'a'; Word != "mate"; Ch++) {
        cout << Word << endl;
        Word[0] = Ch;
    }
    cout << "After loop ends, word is " << Word << endl;

    return 0;
}
