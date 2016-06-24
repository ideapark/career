// Strings.cpp -- storing strings in an array

#include <iostream>
#include <cstring>  // for the strlen() function

int main(void)
{
    using namespace std;
    const int Size = 15;
    char Name1[Size];              // empty array
    char Name2[Size] = "C++owboy"; // initialized array
    // NOTE: some implementations may require the static
    // keyword to initialize the array Name2

    cout << "Howdy! I'm " << Name2;
    cout << "! What's your name?\n";
    cin >> Name1;
    cout << "Well, " << Name1 << ", your name has ";
    cout << strlen(Name1) << " letters and is stored\n";
    cout << "in an array of " << sizeof(Name1) << " bytes.\n";
    cout << "Your initial is " << Name1[0] << ".\n";
    Name2[3] = '\0'; // set to null character
    cout << "Here are the first 3 characters of my name: ";
    cout << Name2 << endl;

    return 0;
}
