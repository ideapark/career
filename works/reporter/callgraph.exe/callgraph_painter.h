/*
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#ifndef CALLGRAPH_PAINTER_H
#define CALLGRAPH_PAINTER_H

#include <map>
#include <string>
#include <fstream>

#include "callgraph_sqlite.h"

namespace callgraph {

class painter
{
public:
	painter();
	~painter();

public:
	void do_work();

private:
	void query_database();
	void paint_dotfile();
	void whole_callgraph();
	void caller_callee_callgraph(int func_key);

private:
	std::map<int, callgraph_entry *> callgraph;
	std::ofstream callgraph_dot;
	std::ofstream callgraph_info;
};

} /* namespace callgraph */

#endif /* CALLGRAPH_PAINTER_H */
