/*
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#include <unistd.h>
#include <sys/stat.h>

#include <string>
#include <cstdlib>
#include <iostream>

#include "popt_options.h"
#include "callgraph_utility.h"
#include "callgraph_options.h"

namespace callgraph {

	namespace options {
		std::string database = "./default.db";
		std::string output   = ".";

		int event_key        = -1;
		int vcpu             = -1;
		int pid              = -1;
		int tid              = -1;

		int func_who         = E_WHOLE; /* enum e_who */
		int func_key         = -1;    /* partial callgraph: function private key */

		int slice_start      = -1;
		int slice_end        = -1;

		float threshold              = 0.001;
		std::string threshold_string = "0.001"; /* It seems like that libpopt
							 * can NOT parse float command
							 * arguments, so I have to use
							 * string, and convert it myself
							 */
	} /* namespace options */

	namespace {
		popt::option options_array[] = {
			popt::option(options::database,         "database",    '\0', "database path",     "database path"),
			popt::option(options::output,           "output",      '\0', "output directory",  "directory path"),
			popt::option(options::event_key,        "event_key",   '\0', "event key",         "number"),
			popt::option(options::vcpu,             "vcpu",        '\0', "vcpu limitation",   "number"),
			popt::option(options::pid,              "pid",         '\0', "process id",        "number"),
			popt::option(options::tid,              "tid",         '\0', "thread id",         "number"),
			popt::option(options::func_who,         "func_who",    '\0', "caller/callee",     "0:caller 1:callee"),
			popt::option(options::func_key,         "func_key",    '\0', "function key",      "number"),
			popt::option(options::slice_start,      "slice_start", '\0', "start slice index", "number"),
			popt::option(options::slice_end,        "slice_end",   '\0', "end slice index",   "number"),
			popt::option(options::threshold_string, "threshold",   '\0', "ratio threshold",   "float"),
		};
	}

	static void check_file(const std::string file)
	{
		struct stat statbuf;

		if (stat(file.c_str(), &statbuf) != 0 || !S_ISREG(statbuf.st_mode)) {
			std::cerr << file << ": does not exists or not a regular file" << std::endl;
			std::exit(-1);
		}
	}

	static void check_dir(const std::string dir)
	{
		struct stat statbuf;

		if (stat(dir.c_str(), &statbuf) != 0 || !S_ISDIR(statbuf.st_mode)) {
			std::cerr << dir << ": does not exists or not a directory" << std::endl;
			std::exit(-1);
		}
	}

	static void check_func_who_and_key(int who, int key)
	{
		if ((who == 0 || who == 1) && key < 0) {
			std::cerr << "function key must be provided when you choose caller/callee"
				  << std::endl;
			std::exit(-1);
		}
	}

	static void check_slice_range(int start, int end)
	{
		if ((start == -1 && end == -1) || (start >= 0 && end >= start))
			/* valid status, fall through */;
		else {
			std::cerr << "slice start and end must be provided BOTH with end >= start or NEITHER"
				  << std::endl;
			std::exit(-1);
		}
	}

	void get_options(int argc, const char *argv[])
	{
		std::vector<std::string> non_options;
		popt::parse_options(argc, argv, non_options);

		lexical_cast<float>(options::threshold_string, options::threshold);

		check_file(options::database);
		check_dir(options::output);
		check_func_who_and_key(options::func_who, options::func_key);
		check_slice_range(options::slice_start, options::slice_end);

		std::cout << std::endl << "------- callgraph.exe -------" << std::endl;
		std::cout << "   database: " << options::database << std::endl;
		std::cout << "     output: " << options::output << std::endl;
		std::cout << "  event_key: " << options::event_key << std::endl;
		std::cout << "       vcpu: " << options::vcpu << std::endl;
		std::cout << "        pid: " << options::pid << std::endl;
		std::cout << "        tid: " << options::tid << std::endl;
		std::cout << "   func_who: " << options::func_who << " (0:caller 1:callee)" << std::endl;
		std::cout << "   func_key: " << options::func_key << std::endl;
		std::cout << "slice_start: " << options::slice_start << std::endl;
		std::cout << "  slice_end: " << options::slice_end << std::endl;
		std::cout << "  threshold: " << options::threshold << std::endl;
	}

} /* namespace callgraph */
