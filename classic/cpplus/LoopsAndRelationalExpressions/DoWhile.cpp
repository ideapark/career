// DoWhile.cpp -- exit-condition loop

#include <iostream>

int main(void)
{
    using namespace std;
    int N;
    cout << "Enter numbers in the range 1-10 to find ";
    cout << "my favorite number\n";
    do {
        cin >> N;      // execute body
    } while (N != 7);  // then test
    cout << "Yes, 7 is my favorite.\n";

    return 0;
}
