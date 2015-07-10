#include <iostream>
#include <set>
#include <vector>
#include <utility>

#include "Query.h"

typedef std::pair<short, short> location;

inline Query::Query() : _solution(0) { }

inline Query::Query(const std::vector<localtion> &loc) 
    : _solution(0), _loc(loc) { }

Query::Query(const Query &rhs) : _loc(rhs._loc), _paren(rhs._paren) {
    if (rhs._solution) {
        _solution = new std::set<short>;
        std::set<short>::iterator it = rhs._solution->begin(),
                                  end_it = rhs._solution->end();
        for ( ; it != end_it; ++it)
            _solution->insert(*it);
    } else {
        _solution = 0;
    }
}

inline Query::~Query() { delete _solution; }

void Query::display() {
    if (!_solution->size()) {
        std::cout << "\n\tSorry, "
            << " no matching lines were found in text.\n"
            << std::endl;
    }
    std::set<short>::const_iterator it = _solution->begin(),
                                    end_it = solution->end();
    for ( ; it != end_it; ++it) {
        int line = *it;
        std::cout << "( " << line+1 << " ) "
            << (*_text_file)[line] << '\n';
    }
    std::cout << std::endl;
}
