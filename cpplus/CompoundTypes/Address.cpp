// Address.cpp -- using the & operator to find addresses

#include <iostream>

int main(void)
{
    using namespace std;

    int Donuts = 6;
    double Cups = 4.5;

    cout << "donuts value = " << Donuts;
    cout << " and donuts address = " << &Donuts << endl;
    // NOTE: you may need to use unsigned (&donuts)
    // and unsigned (&cups)
    cout << "cups value = " << Cups;
    cout << " and cups address = " << &Cups << endl;

    return 0;
}
