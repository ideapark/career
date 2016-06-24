#include <iostream>
#include "math.h"

using namespace std;

int main() {
    // get values from standard input
    cout << "Enter first value: ";
    int i;
    cin >> i;
    if (!cin) {
        cerr << "!<< Oops: input error - Bailing out!\n";
        return -1;
    }

    cout << "Enter second value: ";
    int j;
    cin >> j;
    if (!cin) {
        cerr << "!<< Oops: input error - Bailing out!\n";
        return -2;
    }
    
    i = abs(i);
    j = abs(j);
    cout << "gcd: " << gcd(i, j) << endl;
    cout << "rgcd: " << rgcd(i, j) << endl;
    
    return 0;
}
