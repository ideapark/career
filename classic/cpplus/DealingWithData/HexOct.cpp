// HexOct.cpp -- shows hex and octal literals

#include <iostream>

int main(void)
{
    using namespace std;
    int Chest = 42;    // decimal integer literal
    int Waist = 0x42;  // hexadecimal integer literal
    int Inseam = 042;  // octal integer literal

    cout << "Monsieur cuts a striking figure!\n";
    cout << "Chest = " << Chest << " (42 in decimal)\n";
    cout << "Waist = " << Waist << " (0x42 in hex)\n";
    cout << "Inseam = " << Inseam << " (042 in octal)\n";

    return 0;
}
