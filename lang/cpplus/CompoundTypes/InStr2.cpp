// InStr2.cpp -- reading more than one word with getline

#include <iostream>

int main(void)
{
    using namespace std;
    const int ArSize = 20;
    char Name[ArSize];
    char Dessert[ArSize];

    cout << "Enter your name:\n";
    cin.getline(Name, ArSize); // reads through newline
    cout << "Enter your favourite dessert:\n";
    cin.getline(Dessert, ArSize);
    cout << "I have some delicious " << Dessert;
    cout << " for you, " << Name << ".\n";

    return 0;
}
