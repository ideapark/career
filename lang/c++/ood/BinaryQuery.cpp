#include <iostream>

#include "BinaryQuery.h"

inline std::ostream& BinaryQuery::print(std::ostream &os) const {
	if (_lparen)
		print_lparen(_lparen, os);
	_lop->print(os);
	os << ' ' << _oper << ' ';
	_rop->print(os);
	if (_rparen)
		print_rparen(_rparen, os);
	return os;
}
