// time.h -- Time class before operator overloading

#ifndef TIME_H_
#define TIME_H_

class Time
{
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
    Time Sum(const Time &t) const;
    void Show() const;
};

#endif // TIME_H_
