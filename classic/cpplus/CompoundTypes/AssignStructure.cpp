// AssignStructure.cpp -- assigning structures

#include <iostream>

struct Inflatable {
    char   Name[20];
    float  Volume;
    double Price;
};

int main(void)
{
    using namespace std;

    Inflatable Bouquet = {
        "sunflowers",
        0.20,
        12.49
    };
    Inflatable Choice;
    cout << "bouquet: " << Bouquet.Name << " for $";
    cout << Bouquet.Price << endl;

    Choice = Bouquet; // assign one structure to another
    cout << "choice: " << Choice.Name << " for $";
    cout << Choice.Price << endl;

    return 0;
}
