// Structur.cpp -- a simple structure

#include <iostream>

struct Inflatable { // structure declaration
    char   Name[20];
    float  Volume;
    double Price;
};

int main(void)
{
    using namespace std;
    Inflatable Guest = {
        "Glorious Gloria", // name value
        1.88,              // volume value
        29.99              // price value
    }; // Guest is a structure variable of type Inflatable
    // It's initialized to the indicated values

    Inflatable Pal = {
        "Audacious Arthur",
        3.12,
        32.99
    }; // Pal is a second variable of type Inflatable
    // NOTE: some implementations require using
    // static Inflatable Guest =

    cout << "Expand your guest list width " << Guest.Name;
    cout << " and " << Pal.Name << "!\n";
    // Pal.Name is the name member of the Pal variable
    cout << "You can have both for $";
    cout << Guest.Price + Pal.Price << "!\n";

    return 0;
}
