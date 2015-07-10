// Main.cpp -- example of a three-file program

#include <iostream>
#include "Coordin.h" // structure templates, function prototypes

using namespace std;

int main(void)
{
    Rect RPlace;
    Polar PPlace;
    cout << "Enter the x and y values: ";
    while (cin >> RPlace.X >> RPlace.Y) { // slick use of cin
        PPlace = RectToPolar(RPlace);
        ShowPolar(PPlace);
        cout << "Next two numbers (q to quit): ";
    }
    cout << "Bye!\n";
    return 0;
}
