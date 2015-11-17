/*
 * sysstat/proc/proc_parser.c - sysstat process parser
 *
 * Copyright (C) Zhou Peng <lockrecv@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "core/config.h"
#include "proc/proc.h"
#include "util/sqlite_helper.h"
#include "util/endian_helper.h"

static sqlite_t g_procsqlite;

static proc_list g_proclist = {
    .list.prev = &g_proclist.list,
    .list.next = &g_proclist.list,
};

/*
 * calc process increment within one interval
 */
static void proc_diff(proc_entry *entry)
{
    proc_list *tmp;
    proc_entry entrybak;

    entrybak = *entry;

    list_for_each_entry(tmp, &g_proclist.list, list) {
        if (tmp->entry.pid == entry->pid)
            break;
    }

    if (&tmp->list == &g_proclist.list) {
        tmp = (proc_list *) malloc(sizeof(proc_list));

        list_add_tail(&(tmp->list), &g_proclist.list);

        entry->mem.vm_data = 0;
        entry->mem.vm_exe  = 0;
        entry->mem.vm_hwm  = 0;
        entry->mem.vm_lck  = 0;
        entry->mem.vm_lib  = 0;
        entry->mem.vm_peak = 0;
        entry->mem.vm_pte  = 0;
        entry->mem.vm_rss  = 0;
        entry->mem.vm_size = 0;
        entry->mem.vm_stk  = 0;
        entry->mem.stack_usage = 0;

        entry->ctx.voluntary_ctxt_switch = 0;
        entry->ctx.novoluntary_ctxt_switch = 0;
    } else {
        entry->mem.vm_data -= tmp->entry.mem.vm_data;
        entry->mem.vm_exe  -= tmp->entry.mem.vm_exe;
        entry->mem.vm_hwm  -= tmp->entry.mem.vm_hwm;
        entry->mem.vm_lck  -= tmp->entry.mem.vm_lck;
        entry->mem.vm_lib  -= tmp->entry.mem.vm_lib;
        entry->mem.vm_peak -= tmp->entry.mem.vm_peak;
        entry->mem.vm_pte  -= tmp->entry.mem.vm_pte;
        entry->mem.vm_rss  -= tmp->entry.mem.vm_rss;
        entry->mem.vm_size -= tmp->entry.mem.vm_size;
        entry->mem.vm_stk  -= tmp->entry.mem.vm_stk;
        entry->mem.stack_usage -= tmp->entry.mem.stack_usage;

        entry->ctx.voluntary_ctxt_switch -= tmp->entry.ctx.voluntary_ctxt_switch;
        entry->ctx.novoluntary_ctxt_switch -= tmp->entry.ctx.novoluntary_ctxt_switch;
    }
    tmp->entry = entrybak;
}

static void free_list()
{
    struct list_head *pos, *q;
    proc_list *tmp;

    list_for_each_safe(pos, q, &g_proclist.list) {
        tmp = list_entry(pos, proc_list, list);
        list_del(pos);
        free(tmp);
    }
}

static const char *process_name(const proc_entry *entry, const proc_header *header)
{
    if (entry->name_idx >= 0 && entry->name_idx < PROC_NR)
        return header->proc_names[entry->name_idx];
    else
        return "N/A";
}

int proc_parser(const char *datafile, const char *dbname)
{
    char sqlbuf[SQL_BUFSIZE];
    proc_header header;
    proc_entry entry;
    int fd = -1, i;

    if (sqlite_open(&g_procsqlite, dbname) == -1) {
        fprintf(stderr, "open sqlite database failed.\n");
        goto fail;
    }

    if (sqlite_exec(&g_procsqlite, PROC_CREATE_TABLE_SQL) == -1) {
        fprintf(stderr, "create process table failed.\n");
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

    if (read(fd, &header, sizeof(proc_header)) != sizeof(proc_header)) {
        fprintf(stderr, "read file header failed: %s.\n", datafile);
        goto fail;
    }

    header.count = NTOH32(header.count, header.magic);

    for (i = 0; i < header.count; i++) {
        if (read(fd, &entry, sizeof(proc_entry)) != sizeof(proc_entry)) {
            fprintf(stderr, "read process entry failed.\n");
            break;
        }

        entry.timestamp  = NTOH32(entry.timestamp, header.magic);
        entry.pid        = NTOH32(entry.pid, header.magic);
        entry.name_idx   = NTOH16(entry.name_idx, header.magic);

        entry.mem.vm_peak     = NTOH32(entry.mem.vm_peak, header.magic);
        entry.mem.vm_size     = NTOH32(entry.mem.vm_size, header.magic);
        entry.mem.vm_lck      = NTOH32(entry.mem.vm_lck, header.magic);
        entry.mem.vm_hwm      = NTOH32(entry.mem.vm_hwm, header.magic);
        entry.mem.vm_rss      = NTOH32(entry.mem.vm_rss, header.magic);
        entry.mem.vm_data     = NTOH32(entry.mem.vm_data, header.magic);
        entry.mem.vm_stk      = NTOH32(entry.mem.vm_stk, header.magic);
        entry.mem.vm_exe      = NTOH32(entry.mem.vm_exe, header.magic);
        entry.mem.vm_lib      = NTOH32(entry.mem.vm_lib, header.magic);
        entry.mem.vm_pte      = NTOH32(entry.mem.vm_pte, header.magic);
        entry.mem.stack_usage = NTOH32(entry.mem.stack_usage, header.magic);

        entry.ctx.voluntary_ctxt_switch   = NTOH32(entry.ctx.voluntary_ctxt_switch, header.magic);
        entry.ctx.novoluntary_ctxt_switch = NTOH32(entry.ctx.novoluntary_ctxt_switch, header.magic);

        proc_diff(&entry);

        snprintf(sqlbuf, sizeof(sqlbuf), PROC_INSERT_TABLE_SQL,
                i,
                entry.timestamp,
                entry.pid,
                process_name(&entry, &header),
                entry.mem.vm_peak,
                entry.mem.vm_size,
                entry.mem.vm_lck,
                entry.mem.vm_hwm,
                entry.mem.vm_rss ,
                entry.mem.vm_data,
                entry.mem.vm_stk,
                entry.mem.vm_exe,
                entry.mem.vm_lib,
                entry.mem.vm_pte,
                entry.mem.stack_usage,
                entry.ctx.voluntary_ctxt_switch,
                entry.ctx.novoluntary_ctxt_switch);
        sqlite_exec(&g_procsqlite, sqlbuf);
    }
    close(fd);
    sqlite_close(&g_procsqlite);
    free_list();
    return 0;

fail:
    close(fd);
    sqlite_close(&g_procsqlite);
    free_list();
    return -1;
}
