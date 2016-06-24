#ifndef CPPPRIMER_UTIL_INCLUDE_
#define CPPPRIMER_UTIL_INCLUDE_

#include <iostream>
#include <cstring>
#include <cassert>
#include <iomanip>

class String;

std::istream& operator>>(std::istream &is, String &str);
std::ostream& operator<<(std::ostream &os, const String &str);

class String {
public:
    String();
    String(const char *str);
    String(const String &rhs);
    ~String();

    bool operator==(const String &rhs);
    bool operator==(const char *str);

    String& operator=(const String &rhs);
    String& operator=(const char *str);

    char& operator[](int);

    int size() { return _size; }
    char *c_str() { return _string; }

private:
    int _size;
    char *_string;
};

inline String::String() {
    _size = 0;
    _string = 0;
}

inline String::String(const char *str) {
    if (!str) {
        _size = 0;
        _string = 0;
    } else {
        _size = strlen(str);
        _string = new char[_size+1];
        std::strcpy(_string, str);
    }
}

inline String::String(const String &rhs) {
    _size = rhs._size;
    if (!rhs._string)
        _string = 0;
    else {
        _string = new char[_size+1];
        std::strcpy(_string, rhs._string);
    }
}

inline String::~String() {
    delete[] _string;
    _string = 0;
    _size = 0;
}

inline bool String::operator==(const char *s) {
    return std::strcmp(_string, s) ? false : true;
}

inline String& String::operator=(const char *s) {
    if (!s) {
        _size = 0;
        delete[] _string;
        _string = 0;
    } else {
        _size = strlen(s);
        delete[] _string;
        _string = new char[_size+1];
        std::strcpy(_string, s);
    }
    return *this;
}

inline String& String::operator=(const String &rhs) {
    if (this != &rhs) {
        delete[] _string;
        _size = rhs._size;
        if (!rhs._string)
            _string = 0;
        else {
            _string = new char[_size+1];
            std::strcpy(_string, rhs._string);
        }
    }
    return *this;
}

inline char& String::operator[](int elem) {
    assert(elem >= 0 && elem < _size);
    return _string[elem];
}

inline std::istream& operator>>(std::istream &io, String &s) {
    const int limit_string_size = 4096;
    char inBuf[limit_string_size];
    io >> std::setw(limit_string_size) >> inBuf;
    s = inBuf;
    return io;
}

inline std::ostream& operator<<(std::ostream &os, String &s) {
    return os << s.c_str();
}

#endif // CPPPRIMER_UTIL_INCLUDE_
