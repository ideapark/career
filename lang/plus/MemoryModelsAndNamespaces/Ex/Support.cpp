// Support.cpp -- use external variable
// compile with External.cpp

#include <iostream>

extern double Warming; // use warming from another file

// function prototypes
void Update(double DT);
void Local();

using std::cout;

void Update(double DT)     // modifies global variable
{
    extern double Warming; // optional redeclaration
    Warming += DT; // use global warming
    cout << "Updating global warming to " << Warming;
    cout << " degrees.\n";
}

void Local()              // use local variable
{
    double Warming = 0.8; // new variable hides external one
    cout << "Local warming = " << Warming << " degrees.\n";
    // Access global variable with the
    // scope resolution operator
    cout << "But global warming = " << ::Warming;
    cout << " degrees.\n";
}
