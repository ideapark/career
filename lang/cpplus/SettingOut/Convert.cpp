// Convert.cpp -- converts stone to pounds

#include <iostream>

int StoneToLB(int Stone); // function prototype

int main(void)
{
    using namespace std;

    int Stone;
    cout << "Enter the weight in stone: ";
    cin >> Stone;
    int Pounds = StoneToLB(Stone);
    cout << Stone << " stone = ";
    cout << Pounds << " pounds." << endl;
    return 0;
}

int StoneToLB(int Stone)
{
    return 14 * Stone;
}
