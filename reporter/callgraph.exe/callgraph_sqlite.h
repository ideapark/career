/*
 * Copyright (C) Zhou Peng <lockrecv@qq.com>
 */
#ifndef CALLGRAPH_SQLITE_H
#define CALLGRAPH_SQLITE_H

#include <sqlite3.h>

#include <map>
#include <vector>
#include <string>

namespace callgraph {

enum e_status {
  E_UNVISITED = 0,
  E_VISITED   = 1
};

class callee_entry
{
  public:
    callee_entry(int key, float ratio)
      : func_key(key), call_ratio(ratio) {}

  public:
    int func_key;
    float call_ratio;
};

class callgraph_entry
{
  public:
    callgraph_entry(int k, std::string n, float sr, float tr)
      : func_key(k), name(n), sample_ratio(sr),
        total_ratio(tr), status(E_UNVISITED) {}

  public:
    int func_key;
    std::string name;
    float sample_ratio;
    float total_ratio;
    std::vector<callee_entry *> callees;

    enum e_status status;
};

class callgraph_sqlite
{
  public:
    callgraph_sqlite(const std::string &database);
    ~callgraph_sqlite();

  public:
    long query_sample_count_sum(const std::string &sql);

    void query_callgraph_entry(const std::string &sql,
                               std::map<int, callgraph_entry *> &callgraph);

    void query_callee_entry(const std::string &sql,
                            std::map<int, callgraph_entry *> &callgraph);

  private:
    bool get_table(const std::string &sql, char **&table, int &rows, int &cols);

  private:
    sqlite3 *sqlite_db;
};

} /* namespace callgraph */

#endif /* CALLGRAPH_SQLITE_H */
