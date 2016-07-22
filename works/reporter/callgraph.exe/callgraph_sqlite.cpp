/*
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#include <map>
#include <cstdlib>
#include <string>
#include <iostream>

#include <sqlite3.h>

#include "callgraph_sqlite.h"
#include "callgraph_options.h"

namespace callgraph {

callgraph_sqlite::callgraph_sqlite(const std::string &database)
{
	int rc;

	rc = sqlite3_open(database.c_str(), &sqlite_db);

	if (rc) {
		std::cerr << "------- callgraph.exe -------" << std::endl;
		std::cerr << "open database failed: "
			<< sqlite3_errmsg(sqlite_db) << std::endl;
		std::exit(-1);
	}
}

callgraph_sqlite::~callgraph_sqlite()
{
	sqlite3_close(sqlite_db);
}

bool callgraph_sqlite::get_table(const std::string &sql,
		char **&table,
		int &rows, int &cols)
{
	int rc;
	char *errmsg = 0;

	std::cerr << "------- callgraph.exe -------" << std::endl;
	std::cerr << sql << std::endl << std::endl;

	rc = sqlite3_get_table(sqlite_db, sql.c_str(), &table, &rows, &cols, &errmsg);

	if (rc != SQLITE_OK) {
		std::cerr << "sqlite error: " << errmsg << std::endl;
		std::cerr << sql << std::endl;

		sqlite3_free(errmsg);
		sqlite3_free_table(table);

		return false;
	}

	return true;
}

long callgraph_sqlite::query_sample_count_sum(const std::string &sql)
{
	char **table = 0;
	int rows = 0, cols = 0;
	long result = 0;

	bool ok = get_table(sql, table, rows, cols);

	if (ok && table && rows == 1 && cols == 1 && table[1*cols+0]) {
		result = atol(table[1*cols+0]);
		sqlite3_free_table(table);
	} else {
		std::cerr << "------- callgraph.exe -------" << std::endl;
		std::cerr << "query_sample_count_sum() failed:" << std::endl
			<< sql << std::endl;
	}

	return result;
}

void callgraph_sqlite::query_callgraph_entry(const std::string &sql,
		std::map<int, callgraph_entry *> &callgraph)
{
	char **table = 0;
	int rows = 0, cols = 0;

	bool ok = get_table(sql, table, rows, cols);

	if (!ok || !table)
		return;

	for (int i = 1; i <= rows; i++) {
		int func_private_key = atoi(table[i*cols + 0]);
		std::string func_name = std::string(table[i*cols + 1]);
		float sample_ratio = atof(table[i*cols+2]);
		float total_ratio = atof(table[i*cols+3]);

		std::map<int, callgraph_entry *>::iterator
				iter = callgraph.find(func_private_key),
				end = callgraph.end();

		if (iter == end) {
			callgraph_entry *entry = new callgraph_entry(func_private_key, func_name,
								sample_ratio, total_ratio);
			callgraph.insert(std::make_pair(func_private_key, entry));
		}
	}

	sqlite3_free_table(table);
}

void callgraph_sqlite::query_callee_entry(const std::string &sql,
		std::map<int, callgraph_entry *> &callgraph)
{
	char **table = 0;
	int rows = 0, cols = 0;

	bool ok = get_table(sql, table, rows, cols);

	if (!ok || !table)
		return;

	for (int i = 1; i <= rows; i++) {
		int caller_func_private_key = atoi(table[i*cols + 0]);
		int callee_func_private_key = atoi(table[i*cols + 1]);
		float call_ratio = atof(table[i*cols + 2]);

		int func_key;
		callee_entry *entry;

		/*
		 * HERE WE USED A STRICK TO COMPOSE {caller_entry,[callee_entry]}
		 *
		 *  CASE: E_WHOLE/E_CALLEE
		 *  ======================
		 *
		 *           caller_entry            [caller-1, ..., caller-n]
		 *                                       /               \
		 *                                      /                 \
		 *           callee_entry    [{callee,ratio},...]    [{callee,ratio},...]
		 *
		 *
		 *  CASE: E_CALLER
		 *  ==============
		 *
		 *           caller_entry            [callee-1, ..., callee-n]
		 *                                       /                \
		 *                                      /                  \
		 *           callee_entry    [{caller,ratio},...]    [{caller,ratio},...]
		 *
		 */
		switch (options::func_who) {
		case E_CALLER:
			func_key = callee_func_private_key;
			entry = new callee_entry(caller_func_private_key, call_ratio);
			break;
		case E_WHOLE:
		case E_CALLEE:
			func_key = caller_func_private_key;
			entry = new callee_entry(callee_func_private_key, call_ratio);
			break;
		default:
			std::cerr << "callgraph.exe: got bad cmd options." << std::endl;
			std::exit(-1);
		}

		std::map<int, callgraph_entry *>::iterator
			iter = callgraph.find(func_key),
			end = callgraph.end();

		if (iter != end) {
			callgraph_entry *callgraph_entry = iter->second;
			callgraph_entry->callees.push_back(entry);
		}
	}

	sqlite3_free_table(table);
}

} /* namespace callgraph */
