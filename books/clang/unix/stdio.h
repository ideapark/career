#define NULL      0
#define EOF       (-1)
#define BUFSIZ    1024
#define OPEN_MAX  20

typedef struct _iobuf {
	int  cnt;   /* available char */
	char *ptr;  /* next char address */
	char *base; /* buffer */
	int  flag;  /* file access mode */
	int  fd;    /* file descriptor */
} FILE;

extern FILE _iob[OPEN_MAX];

/*
 * file: stdio.c
 *
 * FILE _iob[OPEN_MAX] = {
 *    {0, (char *)0, (char *)0, _READ, 0},
 *    {0, (char *)0, (char *)0, _WRITE, 1},
 *    {0, (char *)0, (char *)0, _WRITE | _UNBUF, 2}
 * };
 *
 */

#define stdin   (&_iob[0])
#define stdout  (&_iob[1])
#define stderr  (&_iob[2])

enum _flags {
	_READ  = 01,  /* read only mode */
	_WRITE = 02,  /* write mode */
	_UNBUF = 04,  /* no buffer */
	_EOF   = 010, /* end of file */
	_ERR   = 020, /* error occurred */
};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p)    (((p)->flag & _EOF) != 0)
#define ferror(p)  (((p)->flag & _ERR) != 0)
#define fileno(p)  ((p)->fd)

#define getc(p)    (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : fillbuf(p))
#define putc(x,p)  (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _fillbuf((x),p))
#define getchar()  getc(stdin)
#define putchar(x) putc((x),stdout)
