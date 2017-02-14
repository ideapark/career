// Coordin.h -- structure templates and function prototypes
// structure templates

#ifndef COORDIN_H_
#define COORDIN_H_

struct Polar {
    double Distance; // distance from origin
    double Angle;    // direction from origin
};

struct Rect {
    double X; // horizontal distance from origin
    double Y; // vertical distance from origin
};

// prototypes
Polar RectToPolar(const Rect &XYPos);
void ShowPolar(const Polar &DaPos);

#endif // COORDIN_H_
