// time.cpp -- implementing Time methods

#include <iostream>
#include "time.h"

Time::Time()
{
    hours = minutes = 0;
}

Time::Time(int h, int m)
{
    hours = h;
    minutes = m;
}

void Time::AddMin(int m)
{
    minutes += m;
    hours += minutes / MINUTES_PER_HOUR;
    minutes %= MINUTES_PER_HOUR;
}

void Time::AddHr(int h)
{
    hours += h;
}

void Time::Reset(int h, int m)
{
    hours = h;
    minutes = m;
}

Time Time::operator+(const Time &t) const
{
    Time sum;
    sum.minutes = minutes + t.minutes;
    sum.hours = hours + t.hours + sum.minutes / MINUTES_PER_HOUR;
    sum.minutes %= MINUTES_PER_HOUR;
    return sum;
}

Time Time::operator-(const Time &t) const
{
    Time diff;
    int tot1, tot2;
    tot1 = t.minutes + MINUTES_PER_HOUR * t.hours;
    tot2 = minutes + MINUTES_PER_HOUR * hours;
    diff.minutes = (tot2 - tot1) % MINUTES_PER_HOUR;
    diff.hours = (tot2 - tot1) / MINUTES_PER_HOUR;
    return diff;
}

Time Time::operator*(double mult) const
{
    Time result;
    long totalminutes = hours * mult * MINUTES_PER_HOUR + minutes * mult;
    result.hours = totalminutes / MINUTES_PER_HOUR;
    result.minutes = totalminutes % MINUTES_PER_HOUR;
    return result;
}

Time operator*(double mult, const Time &t)
{
    Time result;
    long totalminutes = t.hours * mult * Time::MINUTES_PER_HOUR + t.minutes * mult;
    result.hours = totalminutes / Time::MINUTES_PER_HOUR;
    result.minutes = totalminutes % Time::MINUTES_PER_HOUR;
    return result;
}

std::ostream& operator<<(std::ostream &os, const Time &t)
{
    os << t.hours << " hours, " << t.minutes << " minutes";
    return os;
}
