/*
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#ifndef REPORTER_SQLITE_H
#define REPORTER_SQLITE_H

#include <string>
#include <sqlite3.h>

namespace reporter {

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

} /* namespace reporter */

#endif /* REPORTER_SQLITE_H */
