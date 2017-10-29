#include <utility>
#include "BinaryQuery.h"

class OrQuery : public BinaryQuery {
public:
OrQuery(Query *lop, Query *rop)
        : BinaryQuery(lop, rop) { }
	virtual void eval();
};
