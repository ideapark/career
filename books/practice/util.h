/* error wrapper functions */

#ifndef UTIL_INCLUDE_
#define UTIL_INCLUDE_

extern void eprintf(char*, ...);
extern void weprintf(char*, ...);
extern char* estrdup(char*);
extern void* emalloc(size_t);
extern void* erealloc(void*, size_t);
extern char* progname(void);
extern void setprogname(char*);
extern void usage(void);

/* binary uitls */
void strings(char* name, FILE* fin);

#endif // UTIL_INCLUDE_
