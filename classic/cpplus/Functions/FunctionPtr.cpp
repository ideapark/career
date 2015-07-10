// FunctionPtr.cpp -- pointers to functions

#include <iostream>

double Betsy(int);
double Pam(int);

// second argument is pointer to a type double 
// function that takes a type int argument
void Estimate(int Lines, double (*pF)(int));

int main(void)
{
    using namespace std;
    int Code;
    cout << "How many lines of code do you need? ";
    cin >> Code;
    cout << "Here's Betsy's estimate:\n";
    Estimate(Code, Betsy);
    cout << "Here's Pam's estimate:\n";
    Estimate(Code, Pam);
    return 0;
}

double Betsy(int Lines)
{
    return 0.05 * Lines;
}

double Pam(int Lines)
{
    return 0.03 * Lines + 0.0004 * Lines * Lines;
}

void Estimate(int Lines, double (*pF)(int))
{
    using namespace std;
    cout << Lines << " lines will take ";
    cout << (*pF)(Lines) << " hour(s)\n";
}
