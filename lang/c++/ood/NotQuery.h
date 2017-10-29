#include <vector>
#include <utility>

#include "Query.h"

typedef std::pair<short, short> location;

class NotQuery : public Query {
public:
	virtual void eval();
	const Query *op() const {
		return _op;
	}
	static const std::vector<location> *all_locs() {
		return _all_locs;
	}
protected:
	Query *_op;
	static const std::vector<location> *_all_locs;
};
