// Delete.cpp -- using the delete operator

#include <iostream>
#include <cstring>  // or string.h

using namespace std;

char* GetName(void); // function prototype

int main(void)
{
    char *Name;       // create pointer
    Name = GetName(); // assign address
    cout << Name << "@" << (int*)Name << "\n";
    delete[] Name;    // memory freed

    Name = GetName(); // reuse freed memory
    cout << Name << "@" << (int*)Name << "\n";
    delete[] Name;    // memory freed again

    return 0;
}

// return pointer to new string
char* GetName(void)
{
    char Temp[80]; // temporary storage
    cout << "Enter last name: ";
    cin >> Temp;
    char *PN = new char[strlen(Temp)+1];
    strcpy(PN, Temp); // copy string into smaller space
    return PN;
}
