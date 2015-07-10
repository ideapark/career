#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>

// function object makes it can be inlined
class LessThan {
public:
    bool operator()(const std::string &s1, const std::string &s2) {
        return s1.size() < s2.size();
    }
};

class GreaterThan {
public:
    GreaterThan(int sz = 6) : _size(sz) {}
    int size() { return _size; }
    bool operator()(const std::string &s1) {
        return s1.size() > _size;
    }
private:
    size_t _size;
};

class PrintElem {
public:
    PrintElem(int lineLen = 8) 
        : line_length(lineLen), cnt(0) {}
    void operator()(const std::string &elem) {
        ++cnt;
        if (cnt % line_length == 0)
            std::cout << '\n';
        std::cout << elem << " ";
    }
private:
    int line_length;
    int cnt;
};

typedef std::vector<std::string> textwords;
typedef std::vector<textwords> article;

void process_vocab(article *particle) {
    if (!particle) {
        // warning info
        return;
    }

    textwords texts;
    article::iterator iter = particle->begin();
    article::iterator end = particle->end();
    while (iter != end) {
        std::copy((*iter).begin(), (*iter).end(), back_inserter(texts));
        iter++;
    }

    // sort texts
    std::sort(texts.begin(), texts.end());

    // display
    std::for_each(texts.begin(), texts.end(), PrintElem());
    std::cout << "\n\n";

    // remove duplicated element
    textwords::iterator it;
    it = std::unique(texts.begin(), texts.end());
    texts.erase(it, texts.end());

    // display again
    std::for_each(texts.begin(), texts.end(), PrintElem());
    std::cout << "\n\n";

    // sort by default length 6
    std::stable_sort(texts.begin(), texts.end(), LessThan());
    std::for_each(texts.begin(), texts.end(), PrintElem());
    std::cout << "\n\n";

    // count length greater than 6 
    int cnt = 0;
    cnt = std::count_if(texts.begin(), texts.end(), GreaterThan());
    std::cout << "Number of words greater than length six are "
        << cnt << std::endl;

    // remove words
    static std::string rw[] = { "and", "if", "or", "but", "the" };
    textwords remove_words(rw, rw+5);
    textwords::iterator it2 = remove_words.begin();
    textwords::iterator it2_end = remove_words.end();
    while (it2 != it2_end) {
        int cnt = 0;
        cnt = std::count(texts.begin(), texts.end(), *it2);
        std::cout << cnt << " instance removed: "
            << (*it2) << std::endl;
        texts.erase(
                // std::remove() returns first iterator
                // that should be removed
                std::remove(texts.begin(), texts.end(), *it2),
                texts.end()
                );
        it2++;
    }
    std::cout << "\n\n";
    std::for_each(texts.begin(), texts.end(), PrintElem());
}

int main() {
    article sample;
    textwords t1, t2;
    std::string t1fn, t2fn;

    std::cout << "text file #1: ";
    std::cin >> t1fn;
    std::cout << "text file #2: ";
    std::cin >> t2fn;

    std::ifstream infile1(t1fn.c_str());
    std::ifstream infile2(t2fn.c_str());

    std::istream_iterator<std::string> input_set1(infile1), eos;
    std::istream_iterator<std::string> input_set2(infile2);

    std::copy(input_set1, eos, std::back_inserter(t1));
    std::copy(input_set2, eos, std::back_inserter(t2));

    sample.push_back(t1);
    sample.push_back(t2);

    process_vocab(&sample);

    return 0;
}
