// ArrayStructure.cpp -- an array of structures

#include <iostream>

struct Inflatable {
    char   Name[20];
    float  Volume;
    double Price;
};

int main(void)
{
    using namespace std;

    Inflatable Guests[2] = {         // initializing an array of structs
        { "Bambi", 0.5, 21.99 },     // first structure in array
        { "Godzilla", 2000, 565.99 } // next structure in array
    };

    cout << "The guests " << Guests[0].Name << " and " << Guests[1].Name
         << "\nhave a combined volume of "
         << Guests[0].Volume + Guests[1].Volume << " cubic feet.\n";

    return 0;
}
