/*
 * sysstat/irq/irq.h - sysstat interrupts sample
 *
 * Copyright (c) Zhou Peng <p@ctriple.cn>
 */

#ifndef SYSSTAT_IRQ_H
#define SYSSTAT_IRQ_H

#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include "util/list_helper.h"

#define IRQ_MAXNO     128
#define IRQ_NAMELEN    64
#define IRQ_SERIAL      8 /* serial number string length */
#define SOFTIRQ_SERIAL 64 /* softirq serial number start index */
#define HARDIRQ_SERIAL  0 /* harfirq serial number start index */

#define SOFTIRQ_FILE  "/proc/softirqs"
#define HARDIRQ_FILE  "/proc/interrupts"

#pragma pack(push)
#pragma pack(1)

typedef enum {
	HARD_IRQ = 0,
	SOFT_IRQ = 1,
} irq_t;

typedef struct {
	int32_t magic;
	int8_t cpu_cores;
	int32_t count;
	char irq_names[IRQ_MAXNO][IRQ_NAMELEN];
} irq_header;

typedef struct {
	int32_t timestamp;
	int8_t cpu;
	int8_t irq_type;
	int16_t name_idx;
	int32_t irq_num;
} irq_entry;

#pragma pack(pop)

void irq_init(void);
void irq_run(void);
void irq_exit(void);

#define IRQ_CREATE_TABLE_SQL			\
	"CREATE TABLE IF NOT EXISTS irq_table(" \
	"    private_key   INTEGER,           " \
	"    timestamp     INTEGER,           " \
	"    cpu           INTEGER,           " \
	"    irq_type      TEXT,              " \
	"    name          TEXT,              " \
	"    irq_num       INTEGER            " \
	");"

#define IRQ_INSERT_TABLE_SQL			\
	"INSERT INTO irq_table("		\
	"    private_key,      "		\
	"    timestamp,        "		\
	"    cpu,              "		\
	"    irq_type,         "		\
	"    name,             "		\
	"    irq_num           "		\
	") VALUES (            "		\
	"    %d,               "		\
	"    %"PRId32",        "		\
	"    %d,               "		\
	"    '%s',             "		\
	"    '%s',             "		\
	"    %"PRId32"         "		\
	");"

typedef struct {
	irq_entry entry;
	struct list_head list;
} irq_list;

int irq_parser(const char *datafile, const char *dbname);

#endif /* SYSSTAT_IRQ_H */
