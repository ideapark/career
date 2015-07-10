#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <utility>

typedef std::pair<short, short> location;

class Query {
    friend class NameQuery;
public:
    virtual void eval() = 0;
    virtual std::ostream& print(std::ostream &os = std::cout) const { }
    void display() const;

    const std::set<short> *solution() const;
    const std::vector<location> *locations() const {
        return &_loc;
    }
    static const std::vector<std::string> *text_file() {
        return _text_file;
    }

    void lparen(short lp) { _lparen = lp; }
    void rparen(short rp) { _rparen = rp; }
    short lparen() { return _lparen; }
    short rparen() { return _rparen; }

    void print_lparen(short cnt, std::ostream &os) const;
    void print_rparen(short cnt, std::ostream &os) const;
protected:
    short _lparen;
    short _rparen;
protected:
    Query();
    Query(const Query &rhs);
protected:
    std::set<short> *_vec2set(const std::vector<location>*);
    static std::vector<std::string> *_text_file;
    std::set<short> *_solution;
    std::vector<location> _loc;
private:
    explicit Query(const std::vector<location> &loc);
};

inline const std::set<short>* Query::solution() {
    return _solution ? _solution : _solution = _vec2set(&_loc);
}
