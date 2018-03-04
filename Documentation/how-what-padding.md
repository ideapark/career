# array

padding is satisfied if builtin types are padded.

# union

padding is satisfied when the biggest data type is padded.

# struct

padding is satisfied if each field is padded.

# struct padding

struct animal_struct {
    char dog;           /* 1 bytes */
    unsigned long cat;  /* 4 bytes */
    unsigned short pig; /* 2 bytes */
    char fox;           /* 1 bytes */
};

# compiler padding

struct animal_struct {
    char dog;           /* 1 bytes */
    u8 __pad0[3];       /* 3 bytes */
    unsigned long cat;  /* 4 bytes */
    unsigned short pig; /* 2 bytes */
    char fox;           /* 1 bytes */
    u8 __pad1;          /* 1 bytes */
};

# rearranged struct

struct animal_struct {
    unsigned long cat;  /* 4 bytes */
    unsigned short pig; /* 2 bytes */
    char dog;           /* 1 bytes */
    char fox;           /* 1 bytes */
}

# gcc

gcc -Wpadded: warnning compiler struct padding
