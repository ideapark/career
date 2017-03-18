// Block.cpp -- use a block statement

#include <iostream>

int main(void)
{
    using namespace std;

    cout << "The Amazing Accounto will sum and average ";
    cout << "five numbers for you.\n";
    cout << "Please enter five values:\n";
    double Number;
    double Sum = 0.0;
    for (int i = 1; i <= 5; i++) { // block starts here
        cout << "Value " << i << ": ";
        cin >> Number;
        Sum += Number;
    }                              // block ends here
    cout << "Five exquisite choices indeed! ";
    cout << "They sum to " << Sum << endl;
    cout << "and average to " << Sum/5 << ".\n";
    cout << "The Amazing Accounto bids you adieu!\n";

    return 0;
}
