#include <iostream>
#include "list.h"

int main() {
    ilist mylist;
    std::cout << "\n----------------------------------------------------\n"
              << "test #1: items at end\n"
              << "----------------------------------------------------\n";
    mylist.insert_front(1);
    mylist.insert_front(1);
    mylist.insert_front(1);
    mylist.insert_front(2);
    mylist.insert_front(3);
    mylist.insert_front(4);
    mylist.display();
    int elem_cnt = mylist.remove(1);
    std::cout << "\n" << "Removed " << elem_cnt << " of the value 1\n";
    mylist.display();
    mylist.remove_all();

    std::cout << "\n----------------------------------------------------\n"
              << "test #2: items at front \n"
              << "----------------------------------------------------\n";
    mylist.insert_front(1);
    mylist.insert_front(1);
    mylist.insert_front(1);
    mylist.display();
    elem_cnt = mylist.remove(1);
    std::cout << "\n" << "Removed " << elem_cnt << " of the value 1\n";
    mylist.remove_all();

    std::cout << "\n----------------------------------------------------\n"
              << "test #3: no items present\n"
              << "----------------------------------------------------\n";
    mylist.insert_front(0);
    mylist.insert_front(2);
    mylist.insert_front(4);
    mylist.display();
    elem_cnt = mylist.remove(1);
    std::cout << "\n" << "Removed " << elem_cnt << " of the value 1\n";
    mylist.display();
    mylist.remove_all();

    std::cout << "\n----------------------------------------------------\n"
              << "test #4: items at front and end\n"
              << "----------------------------------------------------\n";
    mylist.insert_front(1);
    mylist.insert_front(1);
    mylist.insert_front(1);
    mylist.insert_front(0);
    mylist.insert_front(2);
    mylist.insert_front(4);
    mylist.insert_front(1);
    mylist.insert_front(1);
    mylist.insert_front(1);
    mylist.display();
    elem_cnt = mylist.remove(1);
    std::cout << "\n" << "Removed " << elem_cnt << " of the value 1\n";
    mylist.display();

    return 0;
}
