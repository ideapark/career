// NameSpace.h

#include <string>

// create the pers and debts namespaces

namespace pers {
    struct Person {
        std::string fname;
        std::string lname;
    };
    void GetPerson(Person &);
    void ShowPerson(const Person &);
}

namespace debts {
    using namespace pers;
    struct Debt {
        Person name;
        double amount;
    };
    void GetDebt(Debt &);
    void ShowDebt(const Debt &);
    double SumDebts(const Debt ar[], int n);
}
