/*
 * sysstat/sys/sys.h - sysstat system info sample
 *
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#ifndef SYSSTAT_SYS_H
#define SYSSTAT_SYS_H

#define __STDC_FORMAT_MACROS
#include <inttypes.h>

#pragma pack(push)
#pragma pack(1)

typedef struct {
	int32_t mem_total;
	int32_t mem_free;
	int32_t mem_buffers;
	int32_t mem_cached;
	int32_t mapped;
	int32_t slab;
	int32_t shmem;
	int32_t swap_total;
	int32_t swap_free;
	int32_t vmalloc_total;
	int32_t vmalloc_used;
	int32_t vmalloc_chunk;
	int32_t hugepage_size;
} sys_mem;

typedef struct {
	int32_t timestamp;
	sys_mem mem;
} sys_entry;

typedef struct {
	int32_t magic;
	int32_t count;
} sys_header;

#pragma pack(pop)

void sys_init(void);
void sys_run(void);
void sys_exit(void);

#define SYS_CREATE_TABLE_SQL			\
	"CREATE TABLE IF NOT EXISTS sys_table(" \
	"    private_key           INTEGER,   " \
	"    timestamp             INTEGER,   " \
	"    mem_total             INTEGER,   " \
	"    mem_free              INTEGER,   " \
	"    mem_buffers           INTEGER,   " \
	"    mem_cached            INTEGER,   " \
	"    mapped                INTEGER,   " \
	"    slab                  INTEGER,   " \
	"    shmem                 INTEGER,   " \
	"    swap_total            INTEGER,   " \
	"    swap_free             INTEGER,   " \
	"    vmalloc_total         INTEGER,   " \
	"    vmalloc_used          INTEGER,   " \
	"    vmalloc_chunk         INTEGER,   " \
	"    hugepage_size         INTEGER    " \
	");"

#define SYS_INSERT_TABLE_SQL			\
	"INSERT INTO sys_table( "		\
	"    private_key,       "		\
	"    timestamp,         "		\
	"    mem_total,         "		\
	"    mem_free,          "		\
	"    mem_buffers,       "		\
	"    mem_cached,        "		\
	"    mapped,            "		\
	"    slab,              "		\
	"    shmem,             "		\
	"    swap_total,        "		\
	"    swap_free,         "		\
	"    vmalloc_total,     "		\
	"    vmalloc_used,      "		\
	"    vmalloc_chunk,     "		\
	"    hugepage_size      "		\
	") VALUES (             "		\
	"    %d,                "		\
	"    %"PRId32",         "		\
	"    %"PRId32",         "		\
	"    %"PRId32",         "		\
	"    %"PRId32",         "		\
	"    %"PRId32",         "		\
	"    %"PRId32",         "		\
	"    %"PRId32",         "		\
	"    %"PRId32",         "		\
	"    %"PRId32",         "		\
	"    %"PRId32",         "		\
	"    %"PRId32",         "		\
	"    %"PRId32",         "		\
	"    %"PRId32",         "		\
	"    %"PRId32"          "		\
	");"

int sys_parser(const char *datafile, const char *dbname);

#endif /* SYSSTAT_SYS_H */
