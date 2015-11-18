/*
 * Copyright (C) Zhou Peng <lockrecv@gmail.com>
 */
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>

#include "callgraph_utility.h"
#include "callgraph_painter.h"
#include "callgraph_options.h"
#include "callgraph_sqlite.h"

namespace callgraph {

static std::string where_and(const std::string &column, int actual, int initial)
{
  std::ostringstream cond;

  if (initial != actual) {
    cond << " AND " << column << " = " << actual << "\n";
    return cond.str();
  } else {
    return "  AND 1 = 1\n";
  }
}

static std::string where_in(const std::string &column, const std::string &table)
{
  std::ostringstream cond;

  cond << "  AND " << column << " IN (" << table << ")\n";

  return cond.str();
}

static std::string where_between(const std::string &column,
                                 int start, int end, int initial)
{
  std::ostringstream cond;

  if (start != initial && end != initial && start <= end) {
    cond << "  AND " << column << " >= " << start << "\n"
         << "  AND " << column << " <= " << end   << "\n";
    return cond.str();
  } else {
    return " AND 1 = 1\n";
  }
}

painter::painter()
{
  std::string dot  = options::output + "/aps-callgraph.dot";
  std::string info = options::output + "/aps-callgraph.info";

  callgraph_dot.open(dot.c_str(), std::ios::out | std::ios::trunc);
  callgraph_info.open(info.c_str(), std::ios::out | std::ios::trunc);

  callgraph_dot << "strict digraph CallGraph {" << std::endl;
  callgraph_dot << "ranksep=1;" << std::endl;
}

painter::~painter()
{
  callgraph_dot << "}";

  callgraph_dot.close();
  callgraph_info.close();

  /*
   * delete callgraph_entry
   */
  std::map<int, callgraph_entry *>::iterator iter = callgraph.begin(),
                                              end = callgraph.end();
  while (iter != end) {
    callgraph_entry *entry = iter->second;

    /*
     * delete callee_entry
     */
    std::vector<callee_entry *>::iterator c_iter = entry->callees.begin(),
                                           c_end = entry->callees.end();
    while (c_iter != c_end) {
      delete *c_iter;
      c_iter++;
    }
    entry->callees.clear();

    delete entry;

    iter++;
  }

  callgraph.clear();
}

void painter::do_work()
{
  query_database();
  paint_dotfile();
}

void painter::query_database()
{
  callgraph_sqlite callgraph_sqlite(options::database);

  std::ostringstream process_keys_sql;

  process_keys_sql << "SELECT process_private_key\n"
                   << "FROM process_info_table\n"
                   << "WHERE 1 = 1\n"
                   << where_and("event_private_key", options::event_key, -1)
                   << where_and("vcpu", options::vcpu, -1)
                   << where_and("pid", options::pid, -1);

  std::ostringstream task_keys_sql;

  task_keys_sql << "SELECT task_private_key\n"
                << "FROM task_info_table\n"
                << "WHERE 1 = 1\n"
                << where_and("event_private_key", options::event_key, -1)
                << where_and("tid", options::tid, -1)
                << where_in("process_private_key", process_keys_sql.str());

  std::ostringstream sample_count_sum_sql;

  sample_count_sum_sql << "SELECT SUM(sample_count) AS sample_count_sum\n"
                       << "FROM task_slice_table\n"
                       << "WHERE 1 = 1\n"
                       << where_between("slice_index", options::slice_start, options::slice_end, -1)
                       << where_and("event_private_key", options::event_key, -1)
                       << where_in("process_private_key", process_keys_sql.str())
                       << where_in("task_private_key", task_keys_sql.str());

  long sample_count_sum = callgraph_sqlite.query_sample_count_sum(sample_count_sum_sql.str());

  if (sample_count_sum <= 0)
    return;

  std::ostringstream fst;

  fst << "SELECT func_private_key,\n"
      << "       ROUND(SUM(sample_count) * 100.0 / " << sample_count_sum << ", 4) AS sample_ratio,\n"
      << "       ROUND(SUM(total_count) * 100.0 / " << sample_count_sum << ", 4) AS total_ratio\n"
      << "FROM func_slice_table\n"
      << "WHERE 1 = 1\n"
      << where_between("slice_index", options::slice_start, options::slice_end, -1)
      << where_in("process_private_key", process_keys_sql.str())
      << where_in("task_private_key", task_keys_sql.str())
      << "GROUP BY func_private_key\n";

  std::ostringstream callgraph_entry_sql;

  callgraph_entry_sql << "SELECT fit.func_private_key,\n"
                      << "       fit.func_name,\n"
                      << "       fst.sample_ratio,\n"
                      << "       fst.total_ratio\n"
                      << "FROM (" << fst.str() << ") AS fst\n"
                      << "LEFT JOIN\n"
                      << "  func_info_table AS fit\n"
                      << "ON fit.func_private_key = fst.func_private_key;\n";

  callgraph_sqlite.query_callgraph_entry(callgraph_entry_sql.str(), callgraph);

  std::ostringstream callee_entry_sql;

  callee_entry_sql << "SELECT caller_func_private_key,\n"
                   << "       callee_func_private_key,\n"
                   << "       ROUND(SUM(call_count) * 100.0 / " << sample_count_sum << ", 4) AS call_ratio\n"
                   << "FROM callgraph_slice_table\n"
                   << "WHERE 1 = 1\n"
                   << where_between("slice_index", options::slice_start, options::slice_end, -1)
                   << where_in("process_private_key", process_keys_sql.str())
                   << where_in("task_private_key", task_keys_sql.str())
                   << "GROUP BY caller_func_private_key,\n"
                   << "         callee_func_private_key;\n";

  callgraph_sqlite.query_callee_entry(callee_entry_sql.str(), callgraph);
}

void painter::paint_dotfile()
{
  switch (options::func_who) {
    case E_WHOLE:
      whole_callgraph();
      break;
    case E_CALLER:
    case E_CALLEE:
      caller_callee_callgraph(options::func_key);
      break;
    default:
      std::cerr << "callgraph.exe: got bad cmd options." << std::endl;
      std::exit(-1);
  }
}

void painter::caller_callee_callgraph(int func_key)
{
  std::map<int, callgraph_entry *>::iterator iter = callgraph.find(func_key),
                                              end = callgraph.end();
  if (iter == end)
    return;

  callgraph_entry *cg_entry = iter->second;

  if (cg_entry->status == E_VISITED)
    return;

  cg_entry->status = E_VISITED;

  if (cg_entry->total_ratio < options::threshold)
    return;

  callgraph_dot << "\"" << cg_entry->func_key << "\""
                << " [color=\"" << get_color(cg_entry->total_ratio) << "\", "
                << " label=\""<< dot_length_limited(cg_entry->name) << "\"];"
                << std::endl;

  callgraph_info << cg_entry->func_key << "|"
                 << cg_entry->name << "|"
                 << std::fixed << std::setprecision(4)
                 << cg_entry->sample_ratio << "|"
                 << std::fixed << std::setprecision(4)
                 << cg_entry->total_ratio << std::endl;

  std::vector<callee_entry *>::iterator c_iter = cg_entry->callees.begin(),
                                         c_end = cg_entry->callees.end();
  while (c_iter != c_end) {
    callee_entry *ce_entry = *c_iter;

    if (ce_entry->call_ratio < options::threshold) {
      c_iter++;
      continue;
    }

    /*
     * graph edge
     */
    switch (options::func_who) {
      case E_CALLEE:
        callgraph_dot << "\"" << cg_entry->func_key << "\" -> "
                      << "\"" << ce_entry->func_key << "\" "
                      << "[label=\""
                      << std::fixed << std::setprecision(4) << ce_entry->call_ratio
                      << "\"];" << std::endl;
        break;
      case E_CALLER:
        callgraph_dot << "\"" << ce_entry->func_key << "\" -> "
                      << "\"" << cg_entry->func_key << "\" "
                      << "[label=\""
                      << std::fixed << std::setprecision(4) << ce_entry->call_ratio
                      << "\"];" << std::endl;
        break;
      default:
        break;
    }
    caller_callee_callgraph(ce_entry->func_key);
    c_iter++;
  }
}

void painter::whole_callgraph()
{
  std::map<int, callgraph_entry *>::iterator iter = callgraph.begin(),
                                              end = callgraph.end();
  while (iter != end) {
    callgraph_entry *cg_entry = iter->second;

    if (cg_entry->total_ratio < options::threshold) {
      iter++;
      continue;
    }

    /*
     * graph node
     */
    callgraph_dot << "\"" << cg_entry->func_key << "\""
                  << " [color=\"" << get_color(cg_entry->total_ratio) << "\", "
                  << " label=\"" << dot_length_limited(cg_entry->name) << "\"];"
                  << std::endl;

    callgraph_info << cg_entry->func_key << "|"
                   << cg_entry->name << "|"
                   << std::fixed << std::setprecision(4)
                   << cg_entry->sample_ratio << "|"
                   << std::fixed << std::setprecision(4)
                   << cg_entry->total_ratio << std::endl;

    std::vector<callee_entry *>::iterator c_iter = cg_entry->callees.begin(),
                                           c_end = cg_entry->callees.end();
    while (c_iter != c_end) {
      callee_entry *ce_entry = *c_iter;

      if (ce_entry->call_ratio < options::threshold) {
        c_iter++;
        continue;
      }

      /*
       * graph edge
       */
      callgraph_dot << "\"" << cg_entry->func_key << "\" -> "
                    << "\"" << ce_entry->func_key << "\" "
                    << "[label=\""
                    << std::fixed << std::setprecision(4) << ce_entry->call_ratio
                    << "\"];" << std::endl;

      c_iter++;
    }

    iter++;
  }
}

} /* namespace callgraph */
