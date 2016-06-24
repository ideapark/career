// Ruler.cpp -- using recursion to subdivide a ruler

#include <iostream>

const int LEN = 66;
const int DIVS = 6;

void SubDivide(char AR[], int Low, int High, int Level);

int main(void)
{
    char Ruler[LEN];
    int I;

    for (I = 1; I < LEN-2; I++)
        Ruler[I] = ' ';
    Ruler[LEN-1] = '\0';

    int Max = LEN - 2;
    int Min = 0;

    Ruler[Min] = Ruler[Max] = '|';
    std::cout << Ruler << std::endl;
    for (I = 1; I <= DIVS; I++) {
        SubDivide(Ruler, Min, Max, I);
        std::cout << Ruler << std::endl;
        for (int J = 1; J < LEN-2; J++)
            Ruler[J] = ' '; // reset to blank ruler
    }
    return 0;
}

void SubDivide(char AR[], int Low, int High, int Level)
{
    if (Level == 0)
        return;
    int Mid = (High+Low)/2;
    AR[Mid] = '|';
    SubDivide(AR, Low, Mid, Level-1);
    SubDivide(AR, Mid, High, Level-1);
}
