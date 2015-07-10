#include <map>
#include <string>
#include <utility>
#include <vector>

#include "Query.h"

typedef std::pair<short, short> location;
typedef std::vector<location> loc;

class NameQuery : public Query {
public:
    explicit NameQuery(const std::string&);
    NameQuery(const std::string&, std::vector<location>*);
public:
    virtual std::ostream& print(std::ostream &os) const;
public:
    void eval();
    std::string name() const {
        return _name;
    }
    static const std::map<std::string, loc*> *word_map() {
        return _word_map;
    }
protected:
    std::string _name;
    static std::map<std::string, loc*> *_word_map;
};
