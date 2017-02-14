// PtrStr.cpp -- using pointers to strings

#include <iostream>
#include <cstring>  // declare strlen(), strcpy()

int main(void)
{
    using namespace std;

    char Animal[20] = "bear";  // animal holds bear
    const char *Bird = "wren"; // bird holds address of string
    char *Ps;                  // uninitialized

    cout << Animal << " and "; // display bear
    cout << Bird << "\n";      // display wren
    // cout << Ps << "\n";     // may display garbage, may cause a crash

    cout << "Enter a kind of animal: ";
    cin >> Animal;             // ok if input < 20 chars
    // cin >> Ps; Too horrible a blunder to try; ps doesn't point to 
    //            allocated space

    Ps = Animal;               // set ps to point to string
    cout << Ps << "!\n";       // ok, same as using animal
    cout << "Before using strcpy():\n";
    cout << Animal << " at " << (int*)Animal << endl;
    cout << Ps << " at " << (int*)Ps << endl;

    Ps = new char[strlen(Animal)+1]; // get new storage
    strcpy(Ps, Animal);              // copy string to new storage
    cout << "After using strcpy():\n";
    cout << Animal << " at " << (int*)Animal << endl;
    cout << Ps << " at " << (int*)Ps << endl;
    delete[] Ps;

    return 0;
}
