// NewStrct.cpp -- using new with a structure

#include <iostream>

// structure definition
struct Inflatable {
    char   Name[20];
    float  Volume;
    double Price;
};

int main(void)
{
    using namespace std;

    Inflatable *PS = new Inflatable; // allocate memory for structure
    cout << "Enter name of inflatable item: ";
    cin.get(PS->Name, 20);           // method 1 for member access
    cout << "Enter volume in cubic feet: ";
    cin >> (*PS).Volume;             // method 2 for member access
    cout << "Enter price: $";
    cin >> PS->Price;
    cout << "Name: " << (*PS).Name << endl;              // method 2
    cout << "Volume: " << PS->Volume << " cubic feet\n"; // method 1
    cout << "Price: $" << PS->Price << endl;             // method 1
    delete PS; // free memory used by structure

    return 0;
}
