// Swaps.cpp -- swapping with references and with pointers

#include <iostream>

void SwapR(int &A, int &B); // a, b are aliases for ints
void SwapP(int *P, int *Q); // p, q are addresses of ints
void SwapV(int A, int B);   // a, b new variables

int main(void)
{
    using namespace std;
    int Wallet1 = 300;
    int Wallet2 = 350;
    cout << "wallet1 = $" << Wallet1;
    cout << " wallet2 = $" << Wallet2 << endl;

    cout << "Using references to swap contents:\n";
    SwapR(Wallet1, Wallet2); // pass variables
    cout << "wallet1 = $" << Wallet1;
    cout << " wallet2 = $" << Wallet2 << endl;

    cout << "Using pointers to swap contents again:\n";
    SwapP(&Wallet1, &Wallet2); // pass addresses of variables
    cout << "wallet1 = $" << Wallet1;
    cout << " wallet2 = $" << Wallet2 << endl;

    cout << "Trying to using passing by value:\n";
    SwapV(Wallet1, Wallet2); // pass values of variables
    cout << "wallet1 = $" << Wallet1;
    cout << " wallet2 = $" << Wallet2 << endl;

    return 0;
}

void SwapR(int &A, int &B)
{
    int Temp;
    Temp = A;
    A = B;
    B = Temp;
}

void SwapP(int *P, int *Q)
{
    int Temp;
    Temp = *P;
    *P = *Q;
    *Q = Temp;
}

void SwapV(int A, int B)
{
    int Temp;
    Temp = A;
    A = B;
    B = Temp;
}
