/*
 * sysstat/sys/sys.c - sysstat system praser
 *
 * Copyright (c) Zhou Peng <p@ctriple.cn>
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include "core/config.h"
#include "sys/sys.h"
#include "util/sqlite_helper.h"
#include "util/endian_helper.h"

static sqlite_t g_sysqlite;
static sys_entry g_lastentry = {.timestamp=0};

/*
 * calc system increment within one interval
 */
static void sys_diff(sys_entry *entry)
{
	sys_entry entrybak;

	entrybak = *entry;
	if (g_lastentry.timestamp == 0) {
		entry->mem.mem_total      = 0;
		entry->mem.mem_free       = 0;
		entry->mem.mem_buffers    = 0;
		entry->mem.mem_cached     = 0;
		entry->mem.mapped         = 0;
		entry->mem.slab           = 0;
		entry->mem.shmem          = 0;
		entry->mem.swap_total     = 0;
		entry->mem.swap_free      = 0;
		entry->mem.vmalloc_total  = 0;
		entry->mem.vmalloc_used   = 0;
		entry->mem.vmalloc_chunk  = 0;
		entry->mem.hugepage_size  = 0;
	} else {
		entry->mem.mem_total      -= g_lastentry.mem.mem_total;
		entry->mem.mem_free       -= g_lastentry.mem.mem_free;
		entry->mem.mem_buffers    -= g_lastentry.mem.mem_buffers;
		entry->mem.mem_cached     -= g_lastentry.mem.mem_cached;
		entry->mem.mapped         -= g_lastentry.mem.mapped;
		entry->mem.slab           -= g_lastentry.mem.slab;
		entry->mem.shmem          -= g_lastentry.mem.shmem;
		entry->mem.swap_total     -= g_lastentry.mem.swap_total;
		entry->mem.swap_free      -= g_lastentry.mem.swap_free;
		entry->mem.vmalloc_total  -= g_lastentry.mem.vmalloc_total;
		entry->mem.vmalloc_used   -= g_lastentry.mem.vmalloc_used ;
		entry->mem.vmalloc_chunk  -= g_lastentry.mem.vmalloc_chunk;
		entry->mem.hugepage_size  -= g_lastentry.mem.hugepage_size;
	}
	g_lastentry = entrybak;
}

int sys_parser(const char *datafile, const char *dbname)
{
	char sqlbuf[SQL_BUFSIZE];
	sys_header header;
	sys_entry entry;
	int fd = -1, i;

	if (sqlite_open(&g_sysqlite, dbname) == -1) {
		fprintf(stderr, "open sqlite database failed.\n");
		goto fail;
	}

	if (sqlite_exec(&g_sysqlite, SYS_CREATE_TABLE_SQL) == -1) {
		fprintf(stderr, "create sys table failed.\n");
		goto fail;
	}

	if (access(datafile, F_OK) != 0) {
		fprintf(stderr, "file does not exist: %s.\n", datafile);
		goto fail;
	}

	if ((fd = open(datafile, O_RDONLY, 0644)) < 0) {
		fprintf(stderr, "open file failed: %s.\n", datafile);
		goto fail;
	}

	if (read(fd, &header, sizeof(header)) != sizeof(header)) {
		fprintf(stderr, "read file header failed: %s.\n", datafile);
		goto fail;
	}

	header.count = NTOH32(header.count, header.magic);

	for (i = 0; i < header.count; i++) {
		if (read(fd, &entry, sizeof(entry)) != sizeof(entry)) {
			fprintf(stderr, "read system entry failed.\n");
			break;
		}

		entry.timestamp         = NTOH32(entry.timestamp, header.magic);
		entry.mem.mem_total     = NTOH32(entry.mem.mem_total, header.magic);
		entry.mem.mem_free      = NTOH32(entry.mem.mem_free, header.magic);
		entry.mem.mem_buffers   = NTOH32(entry.mem.mem_buffers, header.magic);
		entry.mem.mem_cached    = NTOH32(entry.mem.mem_cached, header.magic);
		entry.mem.mapped        = NTOH32(entry.mem.mapped, header.magic);
		entry.mem.slab          = NTOH32(entry.mem.slab, header.magic);
		entry.mem.shmem         = NTOH32(entry.mem.shmem, header.magic);
		entry.mem.swap_total    = NTOH32(entry.mem.swap_total, header.magic);
		entry.mem.swap_free     = NTOH32(entry.mem.swap_free, header.magic);
		entry.mem.vmalloc_total = NTOH32(entry.mem.vmalloc_total, header.magic);
		entry.mem.vmalloc_used  = NTOH32(entry.mem.vmalloc_used, header.magic);
		entry.mem.vmalloc_chunk = NTOH32(entry.mem.vmalloc_chunk, header.magic);
		entry.mem.hugepage_size = NTOH32(entry.mem.hugepage_size, header.magic);

		sys_diff(&entry);

		snprintf(sqlbuf, sizeof(sqlbuf), SYS_INSERT_TABLE_SQL,
			 i,
			 entry.timestamp,
			 entry.mem.mem_total,
			 entry.mem.mem_free,
			 entry.mem.mem_buffers,
			 entry.mem.mem_cached,
			 entry.mem.mapped,
			 entry.mem.slab,
			 entry.mem.shmem,
			 entry.mem.swap_total,
			 entry.mem.swap_free,
			 entry.mem.vmalloc_total,
			 entry.mem.vmalloc_used,
			 entry.mem.vmalloc_chunk,
			 entry.mem.hugepage_size);
		sqlite_exec(&g_sysqlite, sqlbuf);
	}
	close(fd);
	sqlite_close(&g_sysqlite);
	return 0;

fail:
	close(fd);
	sqlite_close(&g_sysqlite);
	return -1;
}
