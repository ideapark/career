#include <functional>
#include "int.h"

int main() {
    std::plus<std::string> stringAdd;
    sres = stringAdd(sval1, sval2);
    dres = BinaryFunc(std::plus<double>(), dval1, dval2);

    std::minus<int> intSub;
    ires = intSub(ival1, ival2);
    dres = BinaryFunc(std::minus<double>(), dval1, dval2);

    std::multiplies< std::complex<int> > complexMultiplies;
    cres = complexMultiplies(cval1, cval2);
    dres = BinaryFunc(std::multiplies<double>(), dval1, dval2);

    std::divides<int> intDivides;
    ires = intDivides(ival1, ival2);
    dres = BinaryFunc(std::divides<double>(), dval1, dval2);

    std::modulus<Int> IntModulus;
    Ires = IntModulus(Ival1, Ival2);
    ires = BinaryFunc(std::modulus<int>(), ival2, ival1);

    std::negate<int> intNegate;
    ires = intNegate(ires);
    Ires = UnaryFunc(std::negate<int>(), Ival1);

    return 0;
}
