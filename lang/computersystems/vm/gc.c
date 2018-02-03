typedef void *ptr;

/*
 * If p points to a word within an allocated block, return pointer to the start
 * of block, else return NULL.
 */
ptr isPtr(ptr p);

/*
 * Return true if block b is marked, else return false.
 */
int blockMarked(ptr b);

/*
 * Return true if block b is allocated, else return false
 */
int blockAllocated(ptr b);

/*
 * Set block b marked
 */
void markBlock(ptr b);

/*
 * Return block b's length in bytes
 */
int length(ptr b);

/*
 * Set block b unmarked from marked
 */
void unmarkBlock(ptr b);

/*
 * Return pointer to block next to block b
 */
ptr nextBlock(ptr b);

void mark(ptr p) {
  if ((b = isPtr(p)) == NULL)
    return;
  if (blockMarked(b))
    return;
  markBlock(b);
  len = length(b);
  for (i=0; i<len; i++)
    mark(b[i]);
  return;
}

void sweep(ptr b, ptr end) {
  while (b < end) {
    if (blockMarked(b))
      unmarkBlock(b);
    else if (blockAllocated(b))
      free(b);
    b = nextBlock(b);
  }
  return;
}
