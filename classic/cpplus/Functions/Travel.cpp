// Travel.cpp -- using structures with functions

#include <iostream>

struct TravelTime {
    int Hours;
    int Minus;
};

const int MINUS_PER_HOUR = 60;

TravelTime Sum(TravelTime T1, TravelTime T2);
void ShowTime(TravelTime T);

int main(void)
{
    using namespace std;
    TravelTime Day1 = { 5, 45 }; // 5 hours, 45 minus
    TravelTime Day2 = { 4, 55 }; // 4 hours, 55 minus
    TravelTime Trip = Sum(Day1, Day2);
    cout << "Two-day total: ";
    ShowTime(Trip);
    TravelTime Day3 = { 4, 32 };
    cout << "Three-day total: ";
    ShowTime(Sum(Trip, Day3));
    return 0;
}

TravelTime Sum(TravelTime T1, TravelTime T2)
{
    TravelTime Total;
    Total.Minus = (T1.Minus + T2.Minus) % MINUS_PER_HOUR;
    Total.Hours = T1.Hours + T2.Hours + (T1.Minus+T2.Minus)/MINUS_PER_HOUR;
    return Total;
}

void ShowTime(TravelTime T)
{
    using namespace std;
    cout << T.Hours << " hours, " << T.Minus << " minutes\n";
}
