// Coordin.cpp -- contains functions called in Main.cpp

#include <iostream>
#include <cmath>
#include "Coordin.h" // structure templates, function prototypes

// convert rectangular to polar coordinates
Polar RectToPolar(const Rect &XYPos)
{
    using namespace std;
    Polar Answer;
    Answer.Distance = sqrt(XYPos.X*XYPos.X + XYPos.Y*XYPos.Y);
    Answer.Angle = atan2(XYPos.Y, XYPos.X);
    return Answer; // returns a polar structure
}

// show polar coordinates, converting angle to degree
void ShowPolar(const Polar &DaPos)
{
    using namespace std;
    const double RadToDeg = 57.29577951;
    cout << "distance = " << DaPos.Distance;
    cout << ", angle = " << DaPos.Angle * RadToDeg;
    cout << " degrees\n";
}
