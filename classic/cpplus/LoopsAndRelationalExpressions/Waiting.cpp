// Waiting.cpp -- using clock() in a time-delay loop

#include <iostream>
#include <ctime>    // describes clock() function, clock_t type

int main(void)
{
    using namespace std;

    cout << "Enter the delay time, in seconds: ";
    float Secs;
    cin >> Secs;
    clock_t Delay = Secs * CLOCKS_PER_SEC; // convert to clock ticks
    cout << "starting\a\n";
    clock_t Start = clock();
    while (clock() - Start < Delay) // wait until time elapses
        ;                           // note the semicolon
    cout << "done\a\n";

    return 0;
}
