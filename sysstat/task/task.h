/*
 * sysstat/task/task.h - sysstat task info sample
 *
 * Copyright (C) Zhou Peng <lockrecv@gmail.com>
 */
#ifndef SYSSTAT_TASK_H
#define SYSSTAT_TASK_H

#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include "util/list_helper.h"

#define TASKPATH_MAX     512

#pragma pack(push)
#pragma pack(1)

typedef struct {
    int32_t magic;
    int32_t count;
} task_header;

typedef struct {
    int32_t timestamp;
    int32_t pid;
    int32_t tid;
    int32_t voluntary_ctxt_switches;
    int32_t nonvoluntary_ctxt_switches;
    int32_t cpu_migration;
} task_entry;

#pragma pack(pop)

void task_init(void);
void task_run(void);
void task_exit(void);

#define TASK_CREATE_TABLE_SQL  \
    "CREATE TABLE IF NOT EXISTS task_table(  " \
    "    private_key                INTEGER, " \
    "    timestamp                  INTEGER, " \
    "    pid                        INTEGER, " \
    "    tid                        INTEGER, " \
    "    voluntary_ctxt_switches    INTEGER, " \
    "    nonvoluntary_ctxt_switches INTEGER, " \
    "    cpu_migration              INTEGER  " \
    ");"

#define TASK_INSERT_TABLE_SQL  \
    "INSERT INTO task_table(         " \
    "    private_key,                " \
    "    timestamp,                  " \
    "    pid,                        " \
    "    tid,                        " \
    "    voluntary_ctxt_switches,    " \
    "    nonvoluntary_ctxt_switches, " \
    "    cpu_migration               " \
    ") VALUES (                      " \
    "    %d,                         " \
    "    %"PRId32",                  " \
    "    %"PRId32",                  " \
    "    %"PRId32",                  " \
    "    %"PRId32",                  " \
    "    %"PRId32",                  " \
    "    %"PRId32"                   " \
    ");"

typedef struct {
    task_entry      entry;
    struct list_head list;
} task_list;

int task_parser(const char *datafile, const char *dbname);

#endif /* SYSSTAT_TASK_H */
