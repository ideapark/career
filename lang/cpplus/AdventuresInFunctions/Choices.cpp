// Choices.cpp -- choosing a template

#include <iostream>

template <class T> // template <typename T>
T Lesser(T A, T B)       // #1
{
    return A < B ? A : B;
}

int Lesser(int A, int B) // #2
{
    A = A < 0 ? -A : A;
    B = B < 0 ? -B : B;
    return A < B ? A : B;
}

int main(void)
{
    using namespace std;
    int M = 20;
    int N = -30;
    double X = 15.5;
    double Y = 25.9;

    cout << Lesser(M, N) << endl;      // use #2
    cout << Lesser(X, Y) << endl;      // use #1 with double
    cout << Lesser<>(M, N) << endl;    // use #1 with int
    cout << Lesser<int>(X, Y) << endl; // use #1 with int

    return 0;
}
