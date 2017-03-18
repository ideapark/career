// FloatNum.cpp -- floating-point types

#include <iostream>

int main(void)
{
    using namespace std;

    cout.setf(ios_base::fixed, ios_base::floatfield); // fixed-point
    float Tub = 10.0 / 3.0;   // good to about 6 places
    double Mint = 10.0 / 3.0; // good to about 15 places
    const float Million = 1.0e6;

    cout << "Tub = " << Tub;
    cout << ", a million Tubs = " << Million * Tub;
    cout << ",\nand ten million Tubs = ";
    cout << 10 * Million * Tub << endl;

    cout << "Mint = " << Mint << " and a million Mints = ";
    cout << Million * Mint << endl;

    return 0;
}
