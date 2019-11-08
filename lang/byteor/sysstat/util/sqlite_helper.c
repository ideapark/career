/*
 * sysstat/util/sqlite_helper.c - sqlite database helper
 *
 * Copyright (c) Zhou Peng <p@ctriple.cn>
 */

#include <stdio.h>
#include <sqlite3.h>

#include "util/sqlite_helper.h"

int sqlite_open(sqlite_t *database, const char *name)
{
	if (sqlite3_open_v2(name, &database->sqlitedb,
			    SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE, NULL) != SQLITE_OK) {
		fprintf(stderr, "open sqlite3 database failed: %s: %s.\n",
			name, sqlite3_errmsg(database->sqlitedb));
		database->status = F_CLOSED;
		database->sqlitedb = NULL;
		return -1;
	} else {
		database->status = F_OPEN;
		sqlite_exec(database, "BEGIN TRANSACTION");
		return 0;
	}
}

int sqlite_exec(sqlite_t *database, const char *sql)
{
	char *errmsg = NULL;

	if (database->status != F_OPEN) {
		fprintf(stderr, "database not open yet!\n");
		return -1;
	}

	if (sqlite3_exec(database->sqlitedb, sql, NULL, NULL, &errmsg) != SQLITE_OK) {
		fprintf(stderr, "sqlite error: %s.\n", errmsg);
		sqlite3_free(errmsg);
		return -1;
	} else {
		return 0;
	}
}

int sqlite_close(sqlite_t *database)
{
	sqlite_exec(database, "COMMIT TRANSACTION");
	sqlite3_close(database->sqlitedb);
	database->sqlitedb = NULL;
	database->status = F_CLOSED;
	return 0;
}
