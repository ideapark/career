class SmallInt {
    friend istream& operator>>(istream &is, SmallInt &s);
    friend ostream& operator<<(ostream &os, const SmallInt &s) {
        return os << s.value;
    }
public:
    SmallInt(int ival=0) : vlaue(ival) {}
    int operator=(int i) {
        return (value = rangeCheck(i));
    }
    // user-defined conversion
    operator int() { return value; }
private:
    int rangeCheck(int);
    int value;
};
