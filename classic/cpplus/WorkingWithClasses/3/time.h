// time.h - Time class after operator overloading

#ifndef TIME_H_
#define TIME_H_

#include <iostream>

class Time
{
    friend Time operator*(double m, const Time &t);
    friend std::ostream& operator<<(std::ostream &os, const Time &t);

private:
    int hours;
    int minutes;

public:
    enum { MINUTES_PER_HOUR = 60 };
    Time();
    Time(int h, int m = 0);
    void AddMin(int m);
    void AddHr(int h);
    void Reset(int h = 0, int m = 0);
    Time operator+(const Time &t) const;
    Time operator-(const Time &t) const;
    Time operator*(double n) const;
};

#endif // TIME_H
