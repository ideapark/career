// MoreAnd.cpp -- using the logical AND operator

#include <iostream>

const char *Qualify[4] = {       // an array of pointers
    "10,000-meter race.\n",      // to strings
    "mud tug-of-war.\n",
    "masters canoe jousting.\n",
    "pie-throwing festival.\n"
};

int main(void)
{
    using namespace std;

    int Age;
    cout << "Enter your age in years: ";
    cin >> Age;
    int Index;

    if (Age > 17 && Age < 35)
        Index = 0;
    else if (Age >= 35 && Age < 50)
        Index = 1;
    else if (Age >= 50 && Age < 65)
        Index = 2;
    else
        Index = 3;
    cout << "You qualify for the " << Qualify[Index];

    return 0;
}
