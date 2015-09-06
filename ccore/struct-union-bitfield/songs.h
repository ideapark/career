#include <stdbool.h>

struct Date {
    short month;
    short day;
    short year;
};

struct Song {
    char title[64];
    char artist[32];
    char composer[32];
    short duration;        // play duration (sec)
    struct Date published; // publish date
};

typedef struct Song Song_t;

typedef struct Cell {
    struct Song song;
    struct Cell *pNext;
} Cell_t;

typedef struct {
    struct Cell *pFirst;
    struct Cell *pLast;
} SongList_t;
