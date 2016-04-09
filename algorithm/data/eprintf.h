/* eprintf.h: error wrapper functions */
extern void eprintf(char *, ...);
extern void weprintf(char *, ...);
extern char *estrdup(char *);
extern void *emalloc(size_t);
extern void *ereallloc(void *, size_t);
extern char *progname(void);
extern void setprogname(char *);
