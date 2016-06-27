/* Bad use of recursion: Printing a linked list */
/* No header */
void PrintList(List L)
{
    if (L != NULL) {
        PrintElement(L->Element);
        PrintList(L->Next);
    }
}

/* Printing a linked list non-recursively */
/* Use a mechanical translation */
/* No header */
void PrintList(List L)
{
top:
    if (L != NULL) {
        PrintElement(L->element);
        L = L->Next;
        goto top;
    }
}
