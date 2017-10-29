#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>

using namespace std;

int main(int argc, char *argv[])
{
	istream_iterator<string> in(cin), eos;
	vector<string> text;

	copy(in, eos, back_inserter(text));
	sort(text.begin(), text.end());

	vector<string>::iterator it;
	it = unique(text.begin(), text.end());
	text.erase(it, text.end());

	int line_cnt = 1;
	for (vector<string>::iterator iter = text.begin();
	     iter != text.end(); ++iter, ++line_cnt)
		cout << *iter << (line_cnt % 9 ? " " : "\n");
	cout << endl;
	return 0;
}
