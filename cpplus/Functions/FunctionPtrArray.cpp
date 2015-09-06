// FunctionPtrArray.cpp -- an array of function pointers
// compile with: -std=c++11

#include <iostream>

// various notations, same signatures
const double *F1(const double AR[], int N);
const double *F2(const double [], int);
const double *F3(const double *, int);

int main(void)
{
    using namespace std;
    double AV[3] = { 1112.3, 1542.6, 2227.9 };

    // pointer to a function
    const double *(*P1)(const double *, int) = F1;
    auto P2 = F2; // C++11 automatic type deduction
    // pre-C++11 can use the following code instead
    // const double *(*P2)(const double *, int) = F2;
    cout << "Using pointers to functions:\n";
    cout << " Address Value\n";
    cout << (*P1)(AV, 3) << ": " << *(*P1)(AV, 3) << endl;
    cout << P2(AV, 3) << ": " << *P2(AV, 3) << endl;

    // pa an array of pointers
    // auto doesn't work with list initialization
    const double *(*PA[3])(const double *, int) = { F1, F2, F3 };
    // but it does work for initializing to a single value
    // pb a pointer to first element of pa
    auto PB = PA;
    // pre-C++11 can use the following code instead
    // const double *(**pb)(const double *, int) = pa;
    cout << "\nUsing an array of pointers to functions:\n";
    cout << " Address Value\n";
    for (int I = 0; I < 3; I++)
        cout << PA[I](AV, 3) << ": " << *PA[I](AV, 3) << endl;
    cout << "\nUsing a pointer to a pointer to a function:\n";
    cout << " Address Value\n";
    for (int I = 0; I < 3; I++)
        cout << PB[I](AV, 3) << ": " << *PB[I](AV, 3) << endl;

    // what about a pointer to an array of function pointers
    cout << "\nUsing pointers to an array of pointers:\n";
    cout << " Address Value\n";
    // easy way to declare pc
    auto PC = &PA;
    // pre-C++11 can use the following code instead
    // const double *(*(*pc)[3])(const double *, int) = &pa;
    cout << (*PC)[0](AV, 3) << ": " << *(*PC)[0](AV, 3) << endl;
    // hard way to declare pd
    const double *(*(*PD)[3])(const double *, int) = &PA;
    // store return value in pdb
    const double *PDB = (*PD)[1](AV, 3);
    cout << PDB << ": " << *PDB << endl;
    // alternative notation
    cout << (*(*PD)[2])(AV, 3) << ": " << *(*(*PD)[2])(AV, 3) << endl;
    return 0;
}

// some rather dull functions
const double *F1(const double *AR, int N)
{
    return AR;
}

const double *F2(const double AR[], int N)
{
    return AR+1;
}

const double *F3(const double AR[], int N)
{
    return AR+2;
}
