// ArrayObject.cpp -- functions with array objects (C++11)
// gcc compiled with: -std=gun++11

#include <iostream>
#include <array>
#include <string>

// constant data
const int Seasons = 4;
const std::array<std::string, Seasons> SNames = {
    "Spring", "Summer", "Fall", "Winter"
};

// function to modify array object
void Fill(std::array<double, Seasons> &RA);
// function that uses array object without modifying it
void Show(const std::array<double, Seasons> &DA);

int main(void)
{
    std::array<double, Seasons> Expenses;
    Fill(Expenses);
    Show(Expenses);
    return 0;
}

void Fill(std::array<double, Seasons> &RA)
{
    using namespace std;
    for (int I = 0; I < Seasons; I++) {
        cout << "Enter " << SNames[I] << " expenses: ";
        cin >> RA[I];
    }
}

void Show(const std::array<double, Seasons> &DA)
{
    using namespace std;
    double Total = 0.0;
    cout << "\nEXPENSES\n";
    for (int I = 0; I < Seasons; I++) {
        cout << SNames[I] << ": $" << DA[I] << endl;
        Total += DA[I];
    }
    cout << "Total Expenses: $" << Total << endl;
}
