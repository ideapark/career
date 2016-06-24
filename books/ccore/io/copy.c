#include <stdio.h>
#include <stdlib.h>

#define ARRAY_LEN 100 // buffer length

typedef struct {
    long key;
    char name[32];
} Record_t;

char inFile[] = "records.dat";
char outFile[] = "packed.dat";

inline void error_exit(int status, const char *error_msg)
{
    fputs(error_msg, stderr);
    exit(status);
}

int main(void)
{
    FILE *fpIn;
    FILE *fpOut;
    Record_t record, *pArray;
    unsigned int i;

    if ((fpIn = fopen(inFile, "rb")) == NULL)
        error_exit(1, "Error on opening input file.");
    else if ((fpOut = fopen(outFile,"wb")) == NULL)
        error_exit(2, "Error on opening output file.");
    else if ((pArray = (Record_t*) malloc(ARRAY_LEN)) == NULL)
        error_exit(3, "Insufficient memory.");
    i = 0;
    while (fread(&record, sizeof(Record_t), 1, fpIn) == 1) {
        if (record.key != 0L) {
            pArray[i++] = record;
            if (i == ARRAY_LEN) {
                if (fwrite(pArray, sizeof(Record_t), i, fpOut) < i)
                    break;
                i = 0;
            }
        }
    }
    if (i > 0)
        fwrite(pArray, sizeof(Record_t), i, fpOut);
    if (ferror(fpOut))
        error_exit(4, "Error on writing to output file.");
    else if (ferror(fpIn))
        error_exit(5, "Error on reading input file.");
    return 0;
}
