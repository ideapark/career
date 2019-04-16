/*
 * sysstat/proc/proc.h - sysstat process sample
 *
 * Copyright (c) Zhou Peng <p@ctriple.cn>
 */

#ifndef SYSSTAT_PROC_H
#define SYSSTAT_PROC_H

#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include "util/list_helper.h"

#define PROC_PATHMAX    512
#define PROC_NAMELEN    64
#define PROC_NR         128

#pragma pack(push)
#pragma pack(1)

typedef struct {
	int32_t vm_peak;
	int32_t vm_size;
	int32_t vm_lck;
	int32_t vm_hwm;
	int32_t vm_rss;
	int32_t vm_data;
	int32_t vm_stk;
	int32_t vm_exe;
	int32_t vm_lib;
	int32_t vm_pte;
	int32_t stack_usage;
} proc_mem;

typedef struct {
	int32_t voluntary_ctxt_switch;
	int32_t novoluntary_ctxt_switch;
} proc_ctx;

typedef struct {
	int32_t  timestamp;
	int32_t  pid;
	int16_t  name_idx;
	proc_mem mem;
	proc_ctx ctx;
} proc_entry;

typedef struct {
	int32_t magic;
	int32_t count;
	char    proc_names[PROC_NR][PROC_NAMELEN];
} proc_header;

#pragma pack(pop)

void proc_init(void);
void proc_run(void);
void proc_exit(void);

#define PROC_CREATE_TABLE_SQL				\
	"create table if not exists proc_table("	\
	"    private_key              integer, "	\
	"    timestamp                integer, "	\
	"    pid                      integer, "	\
	"    name                     TEXT,    "	\
	"    vm_peak                  INTEGER, "	\
	"    vm_size                  INTEGER, "	\
	"    vm_lck                   INTEGER, "	\
	"    vm_hwm                   INTEGER, "	\
	"    vm_rss                   INTEGER, "	\
	"    vm_data                  INTEGER, "	\
	"    vm_stk                   INTEGER, "	\
	"    vm_exe                   INTEGER, "	\
	"    vm_lib                   INTEGER, "	\
	"    vm_pte                   INTEGER, "	\
	"    stack_usage              INTEGER, "	\
	"    voluntary_ctxt_switch    INTEGER, "	\
	"    novoluntary_ctxt_switch  INTEGER  "	\
	");"

#define PROC_INSERT_TABLE_SQL			\
	"INSERT INTO proc_table(      "		\
	"    private_key,             "		\
	"    timestamp,               "		\
	"    pid,                     "		\
	"    name,                    "		\
	"    vm_peak,                 "		\
	"    vm_size,                 "		\
	"    vm_lck,                  "		\
	"    vm_hwm,                  "		\
	"    vm_rss,                  "		\
	"    vm_data,                 "		\
	"    vm_stk,                  "		\
	"    vm_exe,                  "		\
	"    vm_lib,                  "		\
	"    vm_pte,                  "		\
	"    stack_usage,             "		\
	"    voluntary_ctxt_switch,   "		\
	"    novoluntary_ctxt_switch  "		\
	") VALUES (                   "		\
	"    %d,                      "		\
	"    %"PRId32",               "		\
	"    %"PRId32",               "		\
	"    '%s',                    "		\
	"    %"PRId32",               "		\
	"    %"PRId32",               "		\
	"    %"PRId32",               "		\
	"    %"PRId32",               "		\
	"    %"PRId32",               "		\
	"    %"PRId32",               "		\
	"    %"PRId32",               "		\
	"    %"PRId32",               "		\
	"    %"PRId32",               "		\
	"    %"PRId32",               "		\
	"    %"PRId32",               "		\
	"    %"PRId32",               "		\
	"    %"PRId32"                "		\
	");"

typedef struct {
	proc_entry      entry;
	struct list_head list;
} proc_list;

int proc_parser(const char *datafile, const char *dbname);

#endif /* SYSSTAT_PROC_H */
