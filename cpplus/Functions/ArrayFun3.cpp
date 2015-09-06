// ArrayFun3.cpp -- array functions and const

#include <iostream>

const int MAX = 5;

// function prototypes
int FillArray(double Array[], int Limit);
void ShowArray(const double Array[], int N);   // don't change data
void ReValue(double R, double Array[], int N);

int main(void)
{
    using namespace std;

    double Properties[MAX];
    int Size = FillArray(Properties, MAX);
    ShowArray(Properties, Size);
    if (Size > 0) {
        cout << "Enter revaluation factor: ";
        double Factor;
        while (!(cin >> Factor)) { // bad input
            cin.clear();
            while (cin.get() != '\n')
                continue;
            cout << "Bad input; Please enter a number: ";
        }
        ReValue(Factor, Properties, Size);
        ShowArray(Properties, Size);
    }
    cout << "Done.\n";
    cin.get();
    cin.get();
    return 0;
}

int FillArray(double Array[], int Limit)
{
    using namespace std;
    double Temp;
    int I;
    for (I = 0; I < Limit; I++) {
        cout << "Enter value #" << (I+1) << ": ";
        cin >> Temp;
        if (!cin) { // bad input
            cin.clear();
            while (cin.get() != '\n')
                continue;
            cout << "Bad input; input process terminated.\n";
            break;
        } else if (Temp < 0) // signal to terminate
            break;
        Array[I] = Temp;
    }
    return I;
}

// the following function can use, but not alter,
// the array whose address is Array
void ShowArray(const double Array[], int N)
{
    using namespace std;
    for (int I = 0; I < N; I++) {
        cout << "Property #" << (I+1) << ": $";
        cout << Array[I] << endl;
    }
}

// multiplies each element of Array[] by R
void ReValue(double R, double Array[], int N)
{
    for (int I = 0; I < N; I++)
        Array[I] *= R;
}
