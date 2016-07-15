typedef long Align; /* aligned to type long */

union header {             /* block header */
	struct {
		union header *ptr; /* next block in free list */
		unsigned size;     /* block size */
	} s;
	Align x;               /* block aligned */
};

typedef union header Header;

static Header base;          /* empty list */
static Header *freep = NULL; /* free block list */

void *malloc(unsigned nbytes)
{
	Header *p, *prevp;
	Header *morecore(unsigned);
	unsigned nunits;

	nunits = (nbytes+sizeof(Header)-1)/sizeof(Header) + 1;
	if ((prevp = freep) == NULL) { /* no free list */
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;
	}
	for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
		if (p->s.size >= nunits) {       /* big enough */
			if (p->s.size == nunits)
				prevp->s.ptr = p->s.ptr; /* exactly */
			else {                       /* allocate tail block */
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = units;
			}
			freep = prevp;
			return (void *)(p+1);
		}
		if (p == freep)
			if ((p = morecore(nunits)) == NULL)
				return NULL;
	}
}

#define NALLOC 1024  /* minimum allocate units */

static Header *morecore(unsigned nu)
{
	char *cp, *sbrk(int);
	Header *up;

	if (nu < NALLOC)
		nu = NALLOC;
	cp = sbrk(nu * sizeof(Header));
	if (cp == (char *) -1) /* no memory */
		return NULL;
	up = (Header *) cp;
	up->s.size = nu;
	free((void *)(up+1));
	return freep;
}

void free(void *ap)
{
	Header *bp, *p;

	bp = (Header *)ap - 1;
	for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
			break; /* block free at the beginning/end of list */

	if (bp + bp->s.size == p->s.ptr) { /* merged with previous block */
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	} else
		bp->s.ptr = p->s.ptr;
	if (p + p->s.size == bp) {         /* merged with next block */
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	} else
		p->s.ptr = bp;
	freep = p;
}
