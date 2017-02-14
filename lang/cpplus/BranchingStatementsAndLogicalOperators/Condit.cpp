// Condit.cpp -- using the conditional operator

#include <iostream>

int main(void)
{
    using namespace std;

    int A, B;
    cout << "Enter two integers: ";
    cin >> A >> B;
    cout << "The larger of " << A << " and " << B;
    int C = A > B ? A : B; // c = a if a > b, else c = b
    cout << " is " << C << endl;
    return 0;
}
