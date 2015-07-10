#ifndef USER_QUERY_H
#define USER_QUERY_H

#include <string>
#include <vector>
#include <map>
#include <stack>

typedef std::pair<short, short> location;
typedef std::vector<location> loc;

#include "Query.h"

class UserQuery {
public:
    UserQuery(std::vector<std::string> *pquery = 0) 
        : _query(pquery), _eval(0), _paren(0) { }
    Query* eval_query();
    void query(std::vector<std::string> *pq);
    void displayQuery();
    static void word_map(std::map<std::string, 
                                  loc*, 
                                  std::less<std::string> 
                                  > *pwn) {
        if (!_word_map)
            _word_map = pwn;
    }
private:
    enum QueryType { WORD = 1, AND, OR, NOT, RPAREN, LPAREN };
    QueryType evalQueryString(const std::string &query);
    void evalWord(const std::string &query);
    void evalAnd();
    void evalOr();
    void evalNot();
    void evalRParen();
    bool integrity_check();

    int _paren;
    Query *_eval;
    std::vector<std::string> *_query;
    std::stack<Query*, std::vector<Query*> > _query_stack;
    std::stack<Query*, std::vector<Query*> > _current_op;

    static short _lparenOn, _rparenOn;
    static std::map<std::string, loc*, std::less<std::string> > *_word_map;
};

#endif // USER_QUERY_H
