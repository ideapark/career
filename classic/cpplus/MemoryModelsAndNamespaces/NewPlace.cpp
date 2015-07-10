// NewPlace.cpp -- using placement new

#include <iostream>
#include <new>       // for placement new

const int BUF = 512;
const int N = 5;
char Buffer[BUF];    // chunk of memory

int main(void)
{
    using namespace std;
    double *pD1, *pD2;
    int I;
    cout << "Calling new and placement new:\n";
    pD1 = new double[N];          // use heap
    pD2 = new (Buffer) double[N]; // use buffer array
    for (I = 0; I < N; I++)
        pD2[I] = pD1[I] = 1000 + 20.0 * I;
    cout << "Memory addresses:\n" << " heap: " << pD1
         << " static: " << (void*) Buffer << endl;
    cout << "Memory contents:\n";
    for (I = 0; I < N; I++) {
        cout << pD1[I] << " at " << &pD1[I] << "; ";
        cout << pD2[I] << " at " << &pD2[I] << endl;
    }
    cout << "\nCalling new and placement new a second time:\n";
    double *pD3, *pD4;
    pD3 = new double[N];          // find new address
    pD4 = new (Buffer) double[N]; // override old data
    for (I = 0; I < N; I++)
        pD4[I] = pD3[I] = 1000 + 40.0 * I;
    cout << "Memory contents:\n";
    for (I = 0; I < N; I++) {
        cout << pD3[I] << " at " << &pD3[I] << "; ";
        cout << pD4[I] << " at " << &pD4[I] << endl;
    }
    cout << "\nCalling new and placement new a third time:\n";
    delete[] pD1;
    pD1 = new double[N];
    pD2 = new (Buffer + N * sizeof(double)) double[N];
    for (I = 0; I < N; I++)
        pD2[I] = pD1[I] = 1000 + 60.0 * I;
    cout << "Memory contents:\n";
    for (I = 0; I < N; I++) {
        cout << pD1[I] << " at " << &pD1[I] << "; ";
        cout << pD2[I] << " at " << &pD2[I] << endl;
    }
    delete [] pD1;
    delete [] pD3;
    return 0;
}
