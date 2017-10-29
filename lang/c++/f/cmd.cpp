#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>

using namespace std;

const char *const program_name = "comline";
const char *const program_version = "version 0.01 (08/07/97)";

inline void usage(int exit_value = 0) {
	cerr << "usage:\n"
	     << program_name << " "
	     << "[-d] [-h] [-v] \n\t"
	     << "[-o output_file] [-l limit] \n\t"
	     << "file_name [file_name [file_name [file_name [ ... ]]]\n\n"
	     << "where [] indicates optional option: \n\n\t"
	     << "-h: help. \n\t\t"
	     << "generates this message and exits\n\n\t"
	     << "-v: version.\n\t\t"
	     << "prints version information and exits\n\n\t"
	     << "-d: debug.\n\tturns debugging on\n\n\t"
	     << "-l limit\n\t\t"
	     << "limit must be a non-negative integer\n\n\t"
	     << "-o ofile\n\t\t"
	     << "file within which to write out results\n\t\t"
	     << "by default, results written to standard output\n\n"
	     << "file_name\n\t\t"
	     << "the name of the actual file to process\n\t\t"
	     << "at least on file_name is required --\n\t\t"
	     << "any number may be specified\n\n"
	     << "examples:\n\t\t"
	     << "$command chapter7.doc\n\t\t"
	     << "$command -d -l 1024 -o test_7_8 "
	     << "chapter7.doc chapter8.doc\n\n";
	exit(exit_value);
}

int main(int argc, char *argv[]) {
	bool debug_on = false;
	bool ofile_on = false;
	bool limit_on = false;
	int limit = -1;
	string ofile;
	vector<string> file_names;

	cout << "illustration of handling command line arguments:\n"
	     << "argc: " << argc << endl;
	for (int ix = 1; ix < argc; ++ix) {
		cout << "argv[" << ix << "]: "
		     << argv[ix] << endl;
		const char *pchar = argv[ix];
		switch (pchar[0]) {
		case '-': {
			cout << "case \'-\' found\n";
			switch (pchar[1]) {
			case 'd':
				cout << "-d found: "
				     << "debugging truend on\n";
				debug_on = true;
				break;
			case 'v':
				cout << "-v found: "
				     << "version info displayed\n";
				cout << program_name << " :: "
				     << program_version
				     << endl;
				return 0;
			case 'h':
				cout << "-h found: "
				     << "help information\n";
				// no need for break, usage() cause exit
				usage();
			case 'o':
				cout << "-o found: output file\n";
				ofile_on = true;
				break;
			case 'l':
				cout << "-l found: "
				     << "resource limit\n";
				limit_on = true;
				break;
			default:
				cerr << program_name
				     << " : error : "
				     << "unrecognized option: - "
				     << pchar << "\n\n";
				usage(-1);
			}
			break;
		}
		default: {
			cout << "default nonhyphen argument: "
			     << pchar << endl;
			if (ofile_on) {
				ofile_on = false;
				ofile = pchar;
			} else {
				if (limit_on) {
					limit_on = false;
					limit = atoi(pchar);
					if (limit < 0) {
						cerr << program_name
						     << " : error : "
						     << "negative value for limit.\n\n";
						usage(-2);
					}
				} else {
					file_names.push_back(string(pchar));
				}
			}
			break;
		}
		}
	}
	if (file_names.empty()) {
		cerr << program_name
		     << " : error : "
		     << "no file specified for processing.\n\n";
		usage(-3);
	}
	if (limit != -1)
		cout << "User-specified limit: "
		     << limit << endl;
	if (!ofile.empty())
		cout << "User-specified output file: "
		     << ofile << endl;
	cout << (file_names.size() == 1 ? "File " : "Files ")
	     << "to be processed are the following:\n";
	for (int inx = 0; inx < file_names.size(); ++inx)
		cout << "\t" << file_names[inx] << endl;
	return 0;
}
