/* quicksort: sort v[0]..v[n-1] into increasing order */
void quicksort(int v[], int n)
{
    int i, last;

    if (n <= 1) /* nothing to do */
        return;
    swap(v, 0, rand()%n); /* move pivot elem to v[0] */
    last = 0;
    for (i = 1; i < n; i++) /* partition */
        if (v[i] < v[0])
            swap(v, ++last, i);
    swap(v, 0, last);   /* restore pivot */

    quicksort(v, last); /* recursively sort */
    quicksort(v+last+1, n-last-1); /* each part */
}

/* swap: interchange v[i] and v[j] */
void swap(int v[], int i, int j)
{
    int temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* scmp: string compare of *p1 and *p2 */
int scmp(const void* p1, const void* p2)
{
    char* v1, *v2;
    v1 = *(char**)p1;
    v2 = *(char**)p2;
    return strcmp(v1, v2);
}

/* icmp: integer compare of *p1 and *p2 */
int icmp(const void* p1, const void* p2)
{
    int v1, v2;
    v1 = *(int*)p1;
    v2 = *(int*)p2;

    if (v1 < v2)
        return -1;
    else if (v1 == v2)
        return 0;
    else
        return 1;
}

/* lookup: use bsearch to find name in tab, return index */
int lookup(char* name, Nameval tab[], int ntab)
{
    Nameval key, *np;
    key.name = name;
    key.value = 0; /* unused; anything will do */
    np = (Nameval*)bsearch(&key, tab, ntab, sizeof(tab[0]), nvcmp);

    if (np == NULL)
        return -1;
    else
        return np-tab;
}

/* nvcmp: compare two Nameval names */
int nvcmp(const void* va, const void* vb)
{
    const Nameval *a, *b;

    a = (Nameval*)va;
    b = (Nameval*)vb;
    return strcmp(a->name, b->name);
}