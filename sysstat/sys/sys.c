/*
 * sysstat/sys/sys.c - sysstat system sample
 *
 * Copyright (C) Zhou Peng <lockrecv@gmail.com>
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "core/config.h"
#include "core/main.h"
#include "sys/sys.h"
#include "util/misc_helper.h"
#include "util/mapped_helper.h"

static mapfile_t g_sysfile;
static sys_header g_header;

static char *g_buffer;

static int sys_readmeminfo(const char *meminfo, sys_entry *entry)
{
    if (load_procfile(meminfo, g_buffer, PROCFILE_BUFSIZE) < 0)
        return -1;

    keycolon_sscanf("MemTotal", g_buffer, "%"SCNd32, &entry->mem.mem_total);
    keycolon_sscanf("MemFree",  g_buffer, "%"SCNd32, &entry->mem.mem_free);
    keycolon_sscanf("Buffers",  g_buffer, "%"SCNd32, &entry->mem.mem_buffers);
    keycolon_sscanf("Cached",   g_buffer, "%"SCNd32, &entry->mem.mem_cached);
    keycolon_sscanf("Mapped",   g_buffer, "%"SCNd32, &entry->mem.mapped);
    keycolon_sscanf("Slab",     g_buffer, "%"SCNd32, &entry->mem.slab);
    keycolon_sscanf("Shmem",    g_buffer, "%"SCNd32, &entry->mem.shmem);
    keycolon_sscanf("SwapTotal", g_buffer, "%"SCNd32, &entry->mem.swap_total);
    keycolon_sscanf("SwapFree", g_buffer, "%"SCNd32, &entry->mem.swap_free);
    keycolon_sscanf("VmallocTotal", g_buffer, "%"SCNd32, &entry->mem.vmalloc_total);
    keycolon_sscanf("VmallocUsed",  g_buffer, "%"SCNd32, &entry->mem.vmalloc_used);
    keycolon_sscanf("VmallocChunk", g_buffer, "%"SCNd32, &entry->mem.vmalloc_chunk);
    keycolon_sscanf("Hugepagesize", g_buffer, "%"SCNd32, &entry->mem.hugepage_size);

    return 0;
}

static int sys_snapshot(sys_header *header)
{
    const char *path = "/proc/meminfo";

    /* initialized system virtual memory entry */
    sys_entry entry = {
        .timestamp = 0,
        .mem = {
            .mem_total     = 0,
            .mem_free      = 0,
            .mem_buffers   = 0,
            .mem_cached    = 0,
            .mapped        = 0,
            .slab          = 0,
            .shmem         = 0,
            .swap_total    = 0,
            .swap_free     = 0,
            .vmalloc_total = 0,
            .vmalloc_used  = 0,
            .vmalloc_chunk = 0,
            .hugepage_size = 0,
        }
    };

    entry.timestamp = g_timestamp;
    sys_readmeminfo(path, &entry);
    mapped_write(&g_sysfile, (void *)&entry, sizeof(entry));
    header->count++;
    return 0;
}

static int write_sysheader(sys_header *header)
{
    int fd;

    if ((fd = open(SYS_SAMPLEFILE, O_RDWR, 0644)) < 0)
        goto fail;

    if (write(fd, &g_header, sizeof(g_header)) < 0)
        fprintf(stderr, "write system header error.\n");
    close(fd);

    return 0;

fail:
    fprintf(stderr, "write system file header failed.\n");
    return -1;
}

void sys_init(void)
{
    g_header.magic = SYSSTAT_MAGIC;
    g_header.count = 0;

    mapped_open(&g_sysfile, SYS_SAMPLEFILE);
    mapped_write(&g_sysfile, &g_header, sizeof(g_header));

    if ((g_buffer = (char *)malloc(PROCFILE_BUFSIZE)) == NULL) {
        fprintf(stderr, "sys_init failed.\n");
        exit(-1);
    }
}

void sys_run(void)
{
    sys_snapshot(&g_header);
}

void sys_exit(void)
{
    mapped_close(&g_sysfile);
    write_sysheader(&g_header);
    free(g_buffer);
}
