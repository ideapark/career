// External.cpp -- external variables
// compile with Support.cpp

#include <iostream>

using namespace std;

// external variable
double Warming = 0.3; // warming defined

// function prototypes
void Update(double DT);
void Local();

int main(void)
{
    cout << "Global warming is " << Warming << " degrees.\n";
    Update(0.1); // call function to change warming
    cout << "Global warming is " << Warming << " degrees.\n";
    Local();     // call function with local warming
    cout << "Global warming is " << Warming << " degrees.\n";
    return 0;
}
