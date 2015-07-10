// InStr3.cpp -- reading more than one word with get() & get()

#include <iostream>

int main(void)
{
    using namespace std;
    const int ArSize = 20;
    char Name[ArSize];
    char Dessert[ArSize];

    cout << "Enter your name:\n";
    cin.get(Name, ArSize).get(); // read string, newline
    cout << "Enter your favourite dessert:\n";
    cin.get(Dessert, ArSize).get();
    cout << "I have some delicious " << Dessert;
    cout << " for you, " << Name << ".\n";

    return 0;
}
