// MixTypes.cpp -- some type combinations

#include <iostream>

struct AntarcticaYearsEnd {
    int Year;
    /* some really interesting data, etc. */
};

int main(void)
{
    AntarcticaYearsEnd S01, S02, S03;
    S01.Year = 1998;
    AntarcticaYearsEnd *PA = &S02;
    PA->Year = 1999;
    AntarcticaYearsEnd Trio[3]; // array of 3 structures
    Trio[0].Year = 2003;
    std::cout << Trio->Year << std::endl;
    const AntarcticaYearsEnd *Arp[3] = { &S01, &S02, &S03 };
    std::cout << Arp[1]->Year << std::endl;
    const AntarcticaYearsEnd **PPA = Arp;
    auto PPB = Arp; // C++11 automatic type deduction
    // or else use const AntarcticaYearsEnd **PPB = Arp
    std::cout << (*PPA)->Year << std::endl;
    std::cout << (*(PPB+1))->Year << std::endl;

    return 0;
}
