// OurFunc1.cpp -- repositioning the using directive

#include <iostream>

using namespace std; // affects all function definitions in this file

void Simon(int);

int main(void)
{
    Simon(3);
    cout << "Pick an integer: ";
    int Count;
    cin >> Count;
    Simon(Count);
    cout << "Done!" << endl;
    return 0;
}

void Simon(int N)
{
    cout << "Simon says touch your toes " << N << " times." << endl;
}
