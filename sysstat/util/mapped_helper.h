/*
 * sysstat/util/mapped_helper.h - Linux mapped memory file I/O
 *
 * Copyright (C) Zhou Peng <lockrecv@gmail.com>
 */
#ifndef MAPPED_HELPER_H
#define MAPPED_HELPER_H

#include <sys/types.h>

#define MAPPED_PAGES  8

typedef struct {
    int  fd;        /* mmaped memory file descriptor */
    void *addr;     /* start memory address of the maped memory */
    int  used_size; /* used size */
    int  page_size; /* system page size */
} mapfile_t;

/*
 * mapped_open -- open file and mapped to memory
 */
int mapped_open(mapfile_t *mapfile, const char *filename);

/*
 * mapped_write -- write data to mapped file
 */
int mapped_write(mapfile_t *mapfile, const void *data, size_t size);

/*
 * mapped_close -- close mapped file and synchronize data to disk
 */
int mapped_close(mapfile_t *mapfile);

#endif /* MAPPED_HELPER_H */
