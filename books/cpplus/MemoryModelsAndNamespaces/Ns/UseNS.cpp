// UseNS.cpp -- using namespaces

#include <iostream>
#include "NameSpace.h"

void other(void);
void another(void);

int main(void)
{
    using debts::Debt;
    using debts::ShowDebt;
    Debt golf = { {"Benny", "Goatsniff"}, 120.0 };
    ShowDebt(golf);
    other();
    another();
    return 0;
}

void other(void)
{
    using std::cout;
    using std::endl;
    using namespace debts;
    Person dg = { "Doodles", "Glister" };
    ShowPerson(dg);
    cout << endl;
    Debt zippy[3];
    int i;
    for (i = 0; i < 3; i++)
        GetDebt(zippy[i]);
    for (i = 0; i < 3; i++)
        ShowDebt(zippy[i]);
    cout << "Total debt: $" << SumDebts(zippy, 3) << endl;
}

void another(void)
{
    using pers::Person;
    Person collector = { "Milo", "Rightshift" };
    pers::ShowPerson(collector);
    std::cout << std::endl;
}
