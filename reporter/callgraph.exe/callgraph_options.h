/*
 * Copyright (C) Zhou Peng <lockrecv@qq.com>
 */
#ifndef CALLGRAPH_OPTIONS_H
#define CALLGRAPH_OPTIONS_H

#include <string>

namespace callgraph {

enum e_who {
  E_WHOLE  = -1,
  E_CALLER = 0,
  E_CALLEE = 1,
};

namespace options {
  extern std::string database;
  extern std::string output;

  extern int event_key;
  extern int vcpu;
  extern int pid;
  extern int tid;

  extern int func_who;
  extern int func_key;

  extern int slice_start;
  extern int slice_end;
  extern float threshold;
} /* namespace options */

void get_options(int argc, const char *argv[]);

} /* namespace callgraph */

#endif /* CALLGRAPH_OPTIONS_H */
