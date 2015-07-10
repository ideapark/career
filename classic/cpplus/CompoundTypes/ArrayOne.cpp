// ArrayOne.cpp -- small arrays of integers

#include <iostream>

int main(void)
{
    using namespace std;
    int Yams[3]; // creates array with tree elements
    Yams[0] = 7; // assign value to first element
    Yams[1] = 8;
    Yams[2] = 6;

    int YamCosts[3] = { 20, 30, 5 }; // create, initialize array
    // NOTE: If your C++ compiler or translator can't initialize
    // this array, use static int YamCosts[3] instead of 
    // int YamCosts[3]

    cout << "Total Yams = ";
    cout << Yams[0] + Yams[1] + Yams[2] << endl;
    cout << "The package with " << Yams[1] << " Yams costs ";
    cout << YamCosts[1] << " cents per Yam.\n";
    int Total = Yams[0] * YamCosts[0] + Yams[1] * YamCosts[1];
    Total = Total + Yams[2] * YamCosts[2];
    cout << "The total Yam expense is " << Total << " cents.\n";

    cout << "\nSize of Yams array = " << sizeof Yams;
    cout << " bytes.\n";
    cout << "Size of one element = " << sizeof Yams[0];
    cout << " bytes.\n";

    return 0;
}
