// AddPntrs.cpp -- pointer addition

#include <iostream>

int main(void)
{
    using namespace std;

    double Wages[3] = { 10000.0, 20000.0, 30000.0 };
    short Stacks[3] = { 3, 2, 1 };

    // Here are two ways to get the address of an array
    double *Pw = Wages;      // name of an array = address
    short *Ps =  &Stacks[0]; // or use address operator

    // with array element
    cout << "pw = " << Pw << ", *pw = " << *Pw << endl;
    Pw = Pw + 1;
    cout << "add 1 to the pw pointer:\n";
    cout << "pw = " << Pw << ", *pw = " << *Pw << "\n\n";
    cout << "ps = " << Ps << ", *ps = " << *Ps << endl;
    Ps = Ps + 1;
    cout << "add 1 to the ps pointer:\n";
    cout << "ps = " << Ps << ", *ps = " << *Ps << "\n\n";

    cout << "access two elements with array notation\n";
    cout << "stacks[0] = " << Stacks[0]
         << ", stacks[1] = " << Stacks[1] << endl;
    cout << "access two elements with pointer notation\n";
    cout << "*stacks = " << *Stacks
         << ", *(stacks+1) = " << *(Stacks+1) << endl;

    cout << sizeof(Wages) << " = size of wages array\n";
    cout << sizeof(Pw) << " = size of pw pointer\n";

    double (*Pda)[3] = &Wages;
    short (*Psa)[3] = &Stacks;

    cout << "(*pda)[0] = " << (*Pda)[0] << "\n";
    cout << "(*psa)[0] = " << (*Psa)[0] << endl;

    return 0;
}
