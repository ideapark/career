#include <cstring>
#include <iostream>

template<class T>
T max(T t1, T t2) {
    return (t1 > t2 ? t1 : t2);
}

// const char* explicit specialization definition
typedef const char* PCC;

template<>
PCC max<PCC>(PCC s1, PCC s2) {
    return (strcmp(s1, s2) > 0 ? s1 : s2);
}

int main() {
    // int max<int>(int, int);
    int i = max(10, 5);

    // const char* max<const char*>(const char*, const char*);
    const char *p = max("hello", "world");

    std::cout << "i: " << i << "\np: " << p << std::endl;

    return 0;
}
