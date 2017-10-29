#ifndef INT_INCLUDE_H_
#define INT_INCLUDE_H_

#include <vector>
#include <string>
#include <complex>

class Int {
public:
Int(int ival = 0) : _val(ival) {}

	operator int() { return _val; }
	int operator-() { return -_val; }
	int operator%(int ival) { return _val % ival; }
	bool operator<(int ival) { return _val < ival; }
	bool operator!() { return _val == 0; }

private:
	int _val;
};

template <class FuncObject, class Type>
	Type UnaryFunc(FuncObject fob, const Type &val) {
	return fob(val);
}

template <class FuncObject, class Type>
	Type BinaryFunc(FuncObject fob, const Type &val1, const Type &val2) {
	return fob(val1, val2);
}

std::vector<std::string> svec;
std::string sval1, sval2, sres;
std::complex<int> cval1, cval2, cres;
int ival1, ival2, ires;
Int Ival1, Ival2, Ires;
double dval1, dval2, dres;

#endif // INT_INCLUDE_H_
