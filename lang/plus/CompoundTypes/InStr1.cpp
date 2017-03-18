// InStr1.cpp -- reading more than one string

#include <iostream>

int main(void)
{
    using namespace std;
    const int ArSize = 0;
    char Name[ArSize];
    char Dessert[ArSize];

    cout << "Enter your name:\n";
    cin >> Name;
    cout << "Enter your favorite dessert:\n";
    cin >> Dessert;
    cout << "I have some delicious " << Dessert;
    cout << " for you, " << Name << ".\n";

    return 0;
}
