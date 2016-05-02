#include "HashQuad.h"

enum KindOfEntry {Legitimate, Empty, Deleted};

struct HashEntry {
    ElementType      Element;
    enum KindOfEntry Info;
};

typedef struct HashEntry Cell;

/* Cell *TheCells will be an array of */
/* HashEntry cells, allocated later */
struct HashTbl {
    int TableSize;
    Cell *TheCells;
};

HashTable InitializeTable(int TableSize)
{
    HashTable H;
    int i;

    if (TableSize < MinTableSize) {
        Error("Table size too small");
        return NULL;
    }

    /* Allocate table */
    H = malloc(sizeof(struct HashTbl));
    if (H == NULL)
        FatalError("Out of space!!!");

    H->TableSize = NextPrime(TableSize);

    /* Allocate array of Cells */
    H->TheCells = malloc(sizeof(Cell) * H->TableSize);
    if (H->TheCells == NULL)
        FatalError("Out of space!!!");

    for (i = 0; i < H->TableSize; i++)
        H->TheCells[i].Info = Empty;

    return H;
}

Position Find(ElementType Key, HashTable H)
{
    Position CurrentPos;
    int CollisionNum;

    CollisionNum = 0;
    CurrentPos = Hash(Key, H->TableSize);
    while (H->TheCells[CurrentPos].Info != Empty &&
           H->TheCells[CurrentPos].Element != Key) {
        CurrentPos += 2 * ++CollisionNum - 1;
        if (CurrentPos >= H->TableSize)
            CurrentPos += H->TableSize;
    }
    return CurrentPos;
}

void Insert(ElementType Key, HashTable H)
{
    Position Pos;

    Pos = Find(Key, H);
    if (H->TheCells[Pos].Info != Legitimate) {
        /* OK to insert here */
        H->TheCells[Pos].Info = Legitimate;
        H->TheCells[Pos].Element = Key;
    }
}
