#include <iostream>

template <typename Type, int size>
Type min(Type (&r_array)[size]) {
    Type min_val = r_array[0];
    for (int i = 1; i < size; ++i)
        if (r_array[i] < min_val)
            min_val = r_array[i];
    return min_val;
}

int ia[] = { 
    10, 7, 14, 3, 25 
};
float fa[6] = { 
    10.2f, 7.1f, 
    14.5f, 3.2f, 
    25.0f, 16.8f 
};
double da[6] = { 
    10.2, 7.1, 
    14.5, 3.2, 
    25.0, 16.8 
};

int main() {
    int i = min(ia);
    if (i != 3)
        std::cout << "??oops: integer min() failed\n";
    else
        std::cout << "!!ok: integer min() worked\n";

    // function pointer
    float (*pf)(float (&)[6]) = &min;
    float f = pf(fa);
    if (f != 3.2f)
        std::cout << "??oops: float min() failed\n";
    else
        std::cout << "!!ok: float min() worked\n";

    double d = min(da);
    if (d != 3.2)
        std::cout << "??oops: double min() failed\n";
    else
        std::cout << "!!ok: double min() worked\n";

    return 0;
}
