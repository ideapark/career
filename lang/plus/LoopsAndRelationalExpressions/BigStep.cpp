// BigStep.cpp -- count as directed

#include <iostream>

int main(void)
{
    using std::cout; // a using declaration
    using std::cin;
    using std::endl;
    cout << "Enter an integer: ";
    int By;
    cin >> By;
    cout << "Counting by " << By << "s:\n";
    for (int i = 0; i < 100; i = i + By)
        cout << i << endl;
    return 0;
}
