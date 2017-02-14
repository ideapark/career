// StructPtr.cpp -- functions with a structure argument

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
void RectToPolar(const Rect *pXY, Polar *pDa);
void ShowPolar(const Polar *pDaPos);

int main(void)
{
    using namespace std;
    Rect RPlace;
    Polar PPlace;
    cout << "Enter the x and y values: ";
    while (cin >> RPlace.X >> RPlace.Y) { // slick use of cin
        RectToPolar(&RPlace, &PPlace);
        ShowPolar(&PPlace);
        cout << "Next two numbers (q to quit): ";
    }
    cout << "Done.\n";
    return 0;
}

// convert rectangular to ploar coordinates
void RectToPolar(const Rect *pXY, Polar *pDa)
{
    using namespace std;
    pDa->Distance = sqrt(pXY->X*pXY->X + pXY->Y*pXY->Y);
    pDa->Angle = atan2(pXY->Y, pXY->X);
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
