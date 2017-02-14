// Nested.cpp -- nested loops and 2-D array

#include <iostream>

const int CITIES = 5;
const int YEARS  = 4;

int main(void)
{
    using namespace std;

    const char *Cities[CITIES] = { // array of pointers
        "Gribble City",            // to 5 strings
        "Gribbletown",
        "New Gribble",
        "San Gribble",
        "Gribble Vista"
    };

    int MaxTemps[YEARS][CITIES] = {
        { 96, 100, 87, 101, 105 },
        { 96, 89,  91, 107, 104 },
        { 97, 101, 93, 108, 107 },
        { 98, 103, 95, 109, 108 }
    };

    cout << "Maximum temperatures for 2008 - 2011\n\n";
    for (int City = 0; City < CITIES; ++City) {
        cout << Cities[City] << ":\t";
        for (int Year = 0; Year < YEARS; ++Year)
            cout << MaxTemps[Year][City] << "\t";
        cout << endl;
    }

    return 0;
}
