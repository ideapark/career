/*
 * sysstat/irq/irq_parser.c - sysstat interrupts parser
 *
 * Copyright (C) Zhou Peng <lockrecv@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "core/config.h"
#include "irq/irq.h"
#include "util/sqlite_helper.h"
#include "util/endian_helper.h"

static sqlite_t g_irqsqlite;

static irq_list g_irqlist = {
    .list.prev = &g_irqlist.list,
    .list.next = &g_irqlist.list,
};

/*
 * calc interrupt increment within one interval
 */
static void irq_diff(irq_entry *entry)
{
    irq_list *tmp;
    irq_entry entrybak;

    entrybak = *entry;

    list_for_each_entry(tmp, &g_irqlist.list, list) {
        if (tmp->entry.cpu      == entry->cpu &&
            tmp->entry.irq_type == entry->irq_type &&
            tmp->entry.name_idx == entry->name_idx)
            break;
    }

    if (&tmp->list == &g_irqlist.list) {
        tmp = (irq_list *)malloc(sizeof(irq_list));
        list_add_tail(&(tmp->list), &g_irqlist.list);
        entry->irq_num = 0;
    } else {
        entry->irq_num -= tmp->entry.irq_num;
    }
    tmp->entry = entrybak;
}

static void free_list()
{
    struct list_head *pos, *q;
    irq_list *tmp;

    list_for_each_safe(pos, q, &g_irqlist.list) {
        tmp = list_entry(pos, irq_list, list);
        list_del(pos);
        free(tmp);
    }
}

static const char *irq_type(const irq_entry *entry)
{
    if (entry->irq_type == SOFT_IRQ)
        return "soft";
    else if (entry->irq_type == HARD_IRQ)
        return "hard";
    else
        return "N/A";
}

static const char *irq_name(const irq_entry *entry, const irq_header *header)
{
    if (entry->name_idx >= 0 && entry->name_idx < IRQ_MAXNO)
        return header->irq_names[entry->name_idx];
    else
        return "N/A";
}

int irq_parser(const char *datafile, const char *dbname)
{
    char sqlbuf[SQL_BUFSIZE];
    irq_header header;
    irq_entry  entry;
    int fd = -1, i;

    if (sqlite_open(&g_irqsqlite, dbname) == -1) {
        fprintf(stderr, "open sqlite database failed.\n");
        goto fail;
    }

    if (sqlite_exec(&g_irqsqlite, IRQ_CREATE_TABLE_SQL) == -1) {
        fprintf(stderr, "create irq table failed.\n");
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

    if (read(fd, &header, sizeof(irq_header)) != sizeof(irq_header)) {
        fprintf(stderr, "read file header failed: %s.\n", datafile);
        goto fail;
    }

    header.count = NTOH32(header.count, header.magic);

    for (i = 0; i < header.count; i++) {
        if (read(fd, &entry, sizeof(irq_entry)) != sizeof(irq_entry)) {
            fprintf(stderr, "read irq entry failed.\n");
            break;
        }

        entry.timestamp = NTOH32(entry.timestamp, header.magic);
        entry.name_idx = NTOH16(entry.name_idx, header.magic);
        entry.irq_num = NTOH32(entry.irq_num, header.magic);

        irq_diff(&entry);

        snprintf(sqlbuf, sizeof(sqlbuf), IRQ_INSERT_TABLE_SQL,
                i,
                entry.timestamp,
                entry.cpu,
                irq_type(&entry),
                irq_name(&entry, &header),
                entry.irq_num);
        sqlite_exec(&g_irqsqlite, sqlbuf);
    }
    sqlite_close(&g_irqsqlite);
    close(fd);
    free_list();
    return 0;

fail:
    close(fd);
    sqlite_close(&g_irqsqlite);
    free_list();
    return -1;
}
