// TwoTemplates.cpp -- using overloaded template functions

#include <iostream>

template <typename T> // original template
void Swap(T &A, T &B);

template <typename T> // new template
void Swap(T *A, T *B, int N);

void Show(int A[]);

const int LIMIT = 8;

int main(void)
{
    using namespace std;
    int I = 10, J = 20;
    cout << "I, J = " << I << ", " << J << ".\n";
    cout << "Using compiler-generated int swapper:\n";
    Swap(I, J); // matches original template
    cout << "Now I, J = " << I << ", " << J << ".\n";

    int D1[LIMIT] = { 0, 7, 0, 4, 1, 7, 7, 6 };
    int D2[LIMIT] = { 0, 7, 2, 0, 1, 9, 6, 9 };
    cout << "Original arrays:\n";
    Show(D1);
    Show(D2);
    Swap(D1, D2, LIMIT); // matches new template
    cout << "Swapped arrays:\n";
    Show(D1);
    Show(D2);

    return 0;
}

template <typename T>
void Swap(T &A, T &B)
{
    T Temp;
    Temp = A;
    A = B;
    B = Temp;
}

template <typename T>
void Swap(T *A, T *B, int N)
{
    T Temp;
    for (int I = 0; I < N; I++) {
        Temp = A[I];
        A[I] = B[I];
        B[I] = Temp;
    }
}

void Show(int A[])
{
    using namespace std;
    cout << A[0] << A[1] << "/";
    cout << A[2] << A[3] << "/";
    for (int I = 4; I < LIMIT; I++)
        cout << A[I];
    cout << endl;
}
