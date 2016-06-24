#include <stdlib.h>

typedef struct {
    int len;
    float array[10];
} DynArray_t;

int main(void)
{
    DynArray_t *daPtr = malloc(sizeof(DynArray_t) + 10*sizeof(float));
    if (daPtr == NULL)
        exit(-1);

    daPtr->len = 10;
    for (int i = 0; i < daPtr->len; ++i)
        daPtr->array[i] = 1.0F/(i+1);
    /* daPtr->array[10] = 0.1F */ /* invalid array index */

    DynArray_t *daResizePtr = realloc(daPtr, sizeof(DynArray_t) + 11*sizeof(float));
    if (daResizePtr != NULL) {
        daPtr = daResizePtr;
        daPtr->len = 11;
        daPtr->array[10] = 0.1F/12; /* daPtr->array[10] is valid now */
    } else {
        free(daPtr);
        daPtr = NULL;
    }
    free(daResizePtr);
    daResizePtr = NULL;

    return 0;
}
