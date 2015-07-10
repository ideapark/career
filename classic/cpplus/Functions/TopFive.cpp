// TopFive.cpp -- handling an array of string objects

#include <iostream>
#include <string>

using namespace std;

const int SIZE = 5;
void Display(const string SA[], int N);

int main(void)
{
    string List[SIZE]; // an array holding 5 string object
    cout << "Enter your " << SIZE << " favorite astronomical sights:\n";
    for (int I = 0; I < SIZE; I++) {
        cout << I + 1 << ": ";
        getline(cin, List[I]);
    }
    cout << "Your list:\n";
    Display(List, SIZE);
    return 0;
}

void Display(const string SA[], int N)
{
    for (int I = 0; I < N; I++)
        cout << I+1 << ": " << SA[I] << endl;
}
