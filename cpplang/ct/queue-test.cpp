#include <iostream>
#include "queue.h"

int main(int argc, char *argv[])
{
    Queue<int> qi;
    //std::cout << qi << std::endl;
    for (int ival = 0; ival < 10; ++ival)
        qi.add(ival);
    //std::cout << qi << std::endl;
    int err_cnt = 0;
    for (int ival = 0; ival < 10; ++ival) {
        int qval = qi.remove();
        if (ival != qval)
            err_cnt++;
    }
    //std::cout << qi << std::endl;
    if (!err_cnt)
        std::cout << "!! queue executed OK \n";
    else
        std::cerr << "?? queue errors: " << err_cnt << std::endl;
    return 0;
}
