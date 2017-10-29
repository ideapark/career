#include <vector>

#include "BinaryQuery.h"

class AndQuery : public BinaryQuery {
public:
AndQuery(Query *lop, Query *rop)
        : BinaryQuery(lop, rop) { }
	virtual void eval();
	static void max_col(const std::vector<int> *pcol) {
		if (!_max_col)
			_max_col = pcol;
	}
protected:
	static const std::vector<int> *_max_col;
};
