class Screen {
public:
    void *operator new[](size_t);
    void *opeartor new[](size_t, Screen*);
    void operator delete[](void*, size_t);
    void operator delete[](void*, Screen*);
};
