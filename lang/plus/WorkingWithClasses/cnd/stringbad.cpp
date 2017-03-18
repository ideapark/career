// stringbad.cpp -- StringBad class method

#include <cstring>
#include "stringbad.h"

// initializing static class member
int StringBad::num_strings = 0;

// class method

// construct StringBad from C string
StringBad::StringBad(const char *s)
{
    len = std::strlen(s);               // set size
    str = new char[len+1];              // allocate storage
    std::strcpy(str, s);                // initialize pointer
    num_strings++;                      // set object count
    std::cout << num_strings << ": \"" << str
              << "\" object created\n"; // For Your Information
}

StringBad::StringBad()                          // default constructor
{
    len = 4;
    str = new char[4];
    std::strcpy(str, "C++");                    // default string
    num_strings++;
    std::cout << num_strings << ": \"" << str
              << "\" default object created\n"; // FYI
}

StringBad::~StringBad()                    // necessary destructor
{
    std::cout << "\"" << str << "\" object deleted, "; // FYI
    --num_strings;                         // required
    std::cout << num_strings << " left\n"; // FYI
    delete [] str;                         // required
}

std::ostream& operator<<(std::ostream &os, const StringBad &st)
{
    os << st.str;
    return os;
}
