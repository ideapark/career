// Exceed.cpp -- exceeding some integer limits

#include <iostream>
#include <climits> // defines INT_MAX as largest int value

#define ZERO 0     // makes ZERO symbol for 0 value

int main(void)
{
    using namespace std;
    short Sam = SHRT_MAX;     // initialize a variable to max value
    unsigned short Sue = Sam; // okay if variable sam already defined

    cout << "Sam has " << Sam << " dollars and Sue has " << Sue;
    cout << " dollars deposited." << endl
         << "Add $1 to each account." << endl << "Now ";
    Sam = Sam + 1;
    Sue = Sue + 1;
    cout << "Sam has " << Sam << " dollars and Sue has " << Sue;
    cout << " dollars deposited.\nPoor Sam!" << endl;
    Sam = ZERO;
    Sue = ZERO;
    cout << "Sam has " << Sam << " dollars and Sue has " << Sue
         << " dollars deposited." << endl;
    cout << "Take $1 from each account." << endl << "Now ";
    Sam = Sam - 1;
    Sue = Sue - 1;
    cout << "Sam has " << Sam << " dollars and Sue has " << Sue;
    cout << " dollars deposited." << endl << "Lucky Sue!" << endl;
    return 0;
}
