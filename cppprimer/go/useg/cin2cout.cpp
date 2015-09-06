#include <iterator>
#include <algorithm>
#include <iostream>

using namespace std;

int main(void)
{
    copy(istream_iterator<int>(cin), istream_iterator<int>(), 
        ostream_iterator<int>(cout));
    return 0;
}
