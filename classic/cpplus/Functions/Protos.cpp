// Protos.cpp -- using prototypes and function calls

#include <iostream>

void Cheers(int N);    // prototype: no return value
double Cube(double X); // Prototype: returns a double

int main(void)
{
    using namespace std;

    Cheers(5);                  // function call
    cout << "Give me a number: ";
    double Side;
    cin >> Side;
    double Volume = Cube(Side); // function call
    cout << "A " << Side << "-foot cube has volume of ";
    cout << Volume << " cubic feet.\n";
    Cheers(Cube(2)); // prototype protection at work

    return 0;
}

void Cheers(int N)
{
    using namespace std;
    for (int I = 0; I < N; I++)
        cout << "Cheers! ";
    cout << endl;
}

double Cube(double X)
{
    return X * X * X;
}
