// Modulus.cpp -- use % operator to convert lbs to stone

#include <iostream>

int main(void)
{
    using namespace std;

    const int LBS_PER_STN = 14;
    int Lbs;

    cout << "Enter your weight in pounds: ";
    cin >> Lbs;
    int Stone = Lbs / LBS_PER_STN;  // whole stone
    int Pounds = Lbs % LBS_PER_STN; // remainder in pounds
    cout << Lbs << " pounds are " << Stone << " Stone, " 
         << Pounds << " Pound(s).\n";

    return 0;
}
