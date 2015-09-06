// RawStrC11.cpp -- C++11 raw string

#include <iostream>

int main(void)
{
    cout << R"(Jim "King" Tutt uses "\n" instead of endl.)" << '\n';
    cout << "Jim \"King\" Tutt uses \"\\n\" instead of endl." << '\n';
    cout << R"+*("(Who wouldn't?)", she whispered.)+*" << endl;

    return 0;
}
