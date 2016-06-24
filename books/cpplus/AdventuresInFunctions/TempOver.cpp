// TempOver.cpp -- template overloading

#include <iostream>

template <typename T> // template A
void ShowArray(T Arr[], int N);

template <typename T> // template B
void ShowArray(T *Arr[], int N);

struct Debts {
    char Name[50];
    double Amount;
};

int main(void)
{
    using namespace std;
    int Things[6] = { 13, 31, 103, 301, 310, 130 };
    struct Debts MRE[3] = {
        { "Ima Wolfe", 2400.0 },
        { "Ura Foxe", 1300.0 },
        { "Iby Stout", 1800.0 }
    };
    double *PD[3];

    // set pointers to the amount members of the structures in MRE
    for (int I = 0; I < 3; I++)
        PD[I] = &MRE[I].Amount;

    cout << "Listing Mr. E's counts of things:\n";
    // things is an array of int
    ShowArray(Things, 6); // uses templates A
    cout << "Listing Mr. E's debts:\n";
    // pd is an array of pointers to double
    ShowArray(PD, 3); // uses template B (more specialized)
    return 0;
}

    template <typename T>
void ShowArray(T Arr[], int N)
{
    using namespace std;
    cout << "template A\n";
    for (int I = 0; I < N; I++)
        cout << Arr[I] << ' ';
    cout << endl;
}

    template <typename T>
void ShowArray(T *Arr[], int N)
{
    using namespace std;
    cout << "template B\n";
    for (int I = 0; I < N; I++)
        cout << *Arr[I] << ' ';
    cout << endl;
}
