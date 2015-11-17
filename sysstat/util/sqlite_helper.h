/*
 * sysstat/util/sqlite_helper.h - sqlite database helper
 *
 * Copyright (C) Zhou Peng <lockrecv@gmail.com>
 */
#ifndef SQLITE_HELPER_H
#define SQLITE_HELPER_H

#include <sqlite3.h>

typedef enum {
    F_CLOSED = 0,
    F_OPEN   = 1,
} openflag_t;

typedef struct {
    openflag_t status;
    sqlite3 *sqlitedb;
} sqlite_t;

/*
 * sqlite_open -- open database and begin transaction
 */
int sqlite_open(sqlite_t *database, const char *name);

/*
 * sqlite_exec -- execute sql statement
 */
int sqlite_exec(sqlite_t *database, const char *sql);

/*
 * sqlite_close -- close database and commit transaction
 */
int sqlite_close(sqlite_t *database);

#endif /* SQLITE_HELPER_H */
