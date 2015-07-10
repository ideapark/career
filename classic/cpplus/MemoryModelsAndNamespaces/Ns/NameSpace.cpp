// NameSpace.cpp -- namespaces

#include <iostream>
#include "NameSpace.h"

namespace pers {
    using std::cout;
    using std::cin;
    void GetPerson(Person &rp) {
        cout << "Enter first name: ";
        cin >> rp.fname;
        cout << "Enter last name: ";
        cin >> rp.lname;
    }
    void ShowPerson(const Person &rp) {
        std::cout << rp.lname << ", " << rp.fname;
    }
}

namespace debts {
    void GetDebt(Debt &rd) {
        GetPerson(rd.name);
        std::cout << "Enter debt: ";
        std::cin >> rd.amount;
    }
    void ShowDebt(const Debt &rd) {
        ShowPerson(rd.name);
        std::cout << ": $" << rd.amount << std::endl;
    }
    double SumDebts(const Debt ar[], int n) {
        double total = 0;
        for (int i = 0; i < n; i++)
            total += ar[i].amount;
        return total;
    }
}
