// Pointer.cpp -- our first pointer variable

#include <iostream>

int main(void)
{
    using namespace std;

    int Updates = 6; // declare a variable
    int *pUpdates;   // declare pointer to an int

    pUpdates = &Updates; // assign address of int to pointer

    // express values two ways
    cout << "Values: updates = " << Updates;
    cout << ", *p_updates = " << *pUpdates << endl;

    // express address two ways
    cout << "Addresses: &updates = " << &Updates;
    cout << ", p_updates = " << pUpdates << endl;

    // use pointer to change value
    *pUpdates = *pUpdates + 1;
    cout << "Now updates = " << Updates << endl;

    return 0;
}
