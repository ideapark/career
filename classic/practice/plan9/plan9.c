/* errors.h: standard error messages */
enum {
    Eperm,   /* Permission denied */
    Eio,     /* I/O error */
    Efile,   /* File does not exist */
    Emem,    /* Memory limit reached */
    Espace,  /* Out of file space */
    Egreg    /* It's all Greg's fault */
};

/* machine-generated; do not edit */
char *errs[] = {
    "Permission denied",    /* Eperm */
    "I/O error",            /* Eio */
    "File does not exist",  /* Efile */
    "Memory limit reached", /* Emem */
    "Out of file space",    /* Espace */
    "It's all Greg's fault" /* Egreg */
};
