// functor.cpp -- using a functor

#include <list>
#include <iostream>
#include <iterator>
#include <algorithm>


template <class T> // functor class difines operator()()
class TooBig
{
public:
    TooBig(const T &t) : cutoff(t) {}
    bool operator()(const T &v) {
        return v > cutoff;
    }
private:
    T cutoff;
};

void outint(int n) {
    std::cout << n << " ";
}

int main(void)
{
    using namespace std;
    TooBig<int> f100(100); // limit = 100
    int vals[10] = {50, 100, 90, 180, 60, 210, 415, 88, 188, 201};
    list<int> yadayada(vals, vals+10); // reange constructor
    list<int> etcetera(vals, vals+10);
    cout << "Original lists:\n";
    for_each(yadayada.begin(), yadayada.end(), outint);
    cout << endl;
    for_each(etcetera.begin(), etcetera.end(), outint);
    cout << endl;
    yadayada.remove_if(f100);             // use a named function object
    etcetera.remove_if(TooBig<int>(200)); // construct a function object
    cout << "Trimmed lists:\n";
    for_each(yadayada.begin(), yadayada.end(), outint);
    cout << endl;
    for_each(etcetera.begin(), etcetera.end(), outint);
    cout << endl;
    return 0;
}
