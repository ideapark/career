#include <iostream>
#include <string>

#include "NameQuery.h"

inline NameQuery::NameQuery(const std::string &name)
	: _name(name) { }

inline NameQuery::NameQuery(const std::string &name,
			    std::vector<location> *ploc) : _name(name), Query(*ploc) { }

void NameQuery::display_partial_solution(std::ostream &os) {
	os << _name
	   << " is found in "
	   << (_solution ? _solution->size() : 0)
	   << " lines of text\n";
}

void NameQuery::match_count() {
	if (!_solution)
		_solution = _vec2set(&_loc);
	return _solution->size();
}

bool NameQuery::compare(const Query *pquery) {
	int myMatches = _loc.size();
	int intsMatches = pquery->locaions()->size();
	return myMatches == itsMatches;
}

std::ostream& NameQuery::print(std::ostream &os) const {
	if (_lparen)
		print_lparen(_lparen, os);
	os << _name;
	if (_rparen)
		print_rparen(_rparen, os);
	return os;
}
