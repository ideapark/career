// usetime.cpp -- using the second draft of the Time class
// compile usetime.cpp and time.cpp together

#include <iostream>
#include "time.h"

int main(void)
{
    using std::cout;
    using std::endl;

    Time weeding(4, 35);
    Time waxing(2, 47);
    Time total;
    Time diff;
    Time adjusted;

    cout << "weeding time = ";
    cout << weeding;
    cout << endl;

    cout << "waxing time = ";
    cout << waxing;
    cout << endl;

    cout << "total work time = ";
    total = weeding + waxing; // use operator+()
    cout << total;
    cout << endl;

    diff = weeding - waxing;  // use operator-()
    cout << "weeding time - waxing time = ";
    cout << diff;
    cout << endl;

    // use class public operator overloading
    adjusted = total * 1.5;
    cout << "adjusted work time = ";
    cout << adjusted;
    cout << endl;

    // use friend method
    adjusted = 1.5 * total;
    cout << "adjusted work time = ";
    cout << adjusted;
    cout << endl;

    return 0;
}
