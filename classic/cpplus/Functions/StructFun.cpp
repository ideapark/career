// StructFun.cpp -- functions with a structure argument

#include <iostream>
#include <cmath>

// structure declarations
struct Polar {
    double Distance; // distance from origin
    double Angle;    // direction from origin
};

struct Rect {
    double X; // horizontal distance from origin
    double Y; // vertical distance from origin
};

// prototypes
Polar RectToPolar(Rect XYPos);
void ShowPolar(const Polar *pDaPos);

int main(void)
{
    using namespace std;
    Rect RPlace;
    Polar PPlace;
    cout << "Enter the x and y values: ";
    while (cin >> RPlace.X >> RPlace.Y) { // slick use of cin
        PPlace = RectToPolar(RPlace);
        ShowPolar(&PPlace);
        cout << "Next two numbers (q to quit): ";
    }
    cout << "Done.\n";
    return 0;
}

// convert rectangular to ploar coordinates
Polar RectToPolar(Rect XYPos)
{
    using namespace std;
    Polar Answer;
    Answer.Distance = sqrt(XYPos.X*XYPos.X + XYPos.Y*XYPos.Y);
    Answer.Angle = atan2(XYPos.Y, XYPos.X);
    return Answer; // return a polar structure
}

// show polar coordinates, converting angle to degrees
void ShowPolar(const Polar *pDaPos)
{
    using namespace std;
    const double RAD_TO_DEG = 57.29577951;
    cout << "distance = " << pDaPos->Distance;
    cout << ", angle = " << pDaPos->Angle*RAD_TO_DEG;
    cout << " degrees\n";
}
