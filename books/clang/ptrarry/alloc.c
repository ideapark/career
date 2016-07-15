#define ALLOCSIZE 10000 /* avaiable space */

static char allocbuf[ALLOCSIZE]; /* alloc memory area */
static char *allocp = allocbuf;  /* next free pos */

char *alloc(int n)
{
	if (allocbuf + ALLOCSIZE - allocp >= n) { /* enougth free space */
		allocp += n;
		return allocp - n;
	} else {
		return 0;
	}
}

void afree(char *p)
{
	if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}
