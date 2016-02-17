#include "Query.h"

class BinaryQuery : public Query {
public:
    BinaryQuery(Query *lop, Query *rop, std::string oper) 
        : _lop(lop), _rop(rop), _oper(oper) { }
    ~BinaryQuery() {
        delete _lop;
        delete _rop;
    }
    std::ostream& print(std::ostream &os = std::cout) const = 0;
    const Query *lop() { return _lop; }
    const Query *rop() { return _rop; }
protected:
    Query *_lop;
    Query *_rop;
    std::string _oper;
};
