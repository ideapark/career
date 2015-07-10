// use_algo.cpp -- using several stl elements

#include <map>
#include <set>
#include <vector>
#include <string>
#include <cctype>
#include <iterator>
#include <iostream>
#include <algorithm>

using namespace std;

char char2lower(char ch) {
    return tolower(ch);
}

string& str2lower(string &st);
void display(const string &s);

int main(void)
{
    vector<string> words;
    cout << "Enter words (enter quit to quit):\n";
    string input;
    while (cin >> input && input != "quit")
        words.push_back(input);
    cout << "You entered the following words:\n";
    for_each(words.begin(), words.end(), display);
    cout << endl;

    // place words in set, converting to lower case
    set<string> wordset;
    transform(words.begin(), words.end(), insert_iterator<set<string> >(
                wordset, wordset.begin()), str2lower);
    cout << "\nAlphabetic list of words:\n";
    for_each(wordset.begin(), wordset.end(), display);
    cout << endl;

    // place word and frequency in map
    map<string, int> wordmap;
    set<string>::iterator si;
    for (si = wordset.begin(); si != wordset.end(); si++)
        wordmap[*si] = count(words.begin(), words.end(), *si);

    // display map contents
    cout << "\nWord frequency:\n";
    for (si = wordset.begin(); si != wordset.end(); si++)
        cout << *si << ": " << wordmap[*si] << endl;

    return 0;
}

string& str2lower(string &st)
{
    transform(st.begin(), st.end(), st.begin(), char2lower);
    return st;
}

void display(const string &s)
{
    cout << s << " ";
}
