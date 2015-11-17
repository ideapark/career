/*
 * sysstat/task/task_parser.c - sysstat task parser
 *
 * Copyright (C) Zhou Peng <lockrecv@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "core/config.h"
#include "task/task.h"
#include "util/sqlite_helper.h"
#include "util/endian_helper.h"

static sqlite_t g_tasksqlite;

static task_list g_tasklist = {
  .list.prev = &g_tasklist.list,
  .list.next = &g_tasklist.list,
};

/*
 * calc task increment within one interval
 */
static void task_diff(task_entry *entry)
{
  task_list *tmp;
  task_entry entrybak;

  entrybak = *entry;

  list_for_each_entry(tmp, &g_tasklist.list, list) {
    if (tmp->entry.pid == entry->pid && tmp->entry.tid == entry->tid)
      break;
  }

  if (&tmp->list == &g_tasklist.list) {
    tmp = (task_list *) malloc(sizeof(task_list));

    list_add_tail(&(tmp->list), &g_tasklist.list);

    entry->nonvoluntary_ctxt_switches = 0;
    entry->voluntary_ctxt_switches = 0;
    entry->cpu_migration = 0;
  } else {
    entry->voluntary_ctxt_switches -= tmp->entry.voluntary_ctxt_switches;
    entry->nonvoluntary_ctxt_switches -= tmp->entry.nonvoluntary_ctxt_switches;
    entry->cpu_migration -= tmp->entry.cpu_migration;
  }
  tmp->entry = entrybak;
}

static void free_list()
{
  struct list_head *pos, *q;
  task_list *tmp;

  list_for_each_safe(pos, q, &g_tasklist.list) {
    tmp = list_entry(pos, task_list, list);
    list_del(pos);
    free(tmp);
  }
}

int task_parser(const char *datafile, const char *dbname)
{
  char sqlbuf[SQL_BUFSIZE];
  task_header header;
  task_entry entry;
  int fd = -1, i;

  if (sqlite_open(&g_tasksqlite, dbname) == -1) {
    fprintf(stderr, "open sqlite database failed.\n");
    goto fail;
  }

  if (sqlite_exec(&g_tasksqlite, TASK_CREATE_TABLE_SQL) == -1) {
    fprintf(stderr, "create task table failed.\n");
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

  if (read(fd, &header, sizeof(task_header)) != sizeof(task_header)) {
    fprintf(stderr, "read file header failed: %s.\n", datafile);
    goto fail;
  }

  header.count = NTOH32(header.count, header.magic);

  for (i = 0; i < header.count; i++) {
    if (read(fd, &entry, sizeof(task_entry)) != sizeof(task_entry)) {
      fprintf(stderr, "read task entry failed.\n");
      break;
    }

    entry.timestamp                  = NTOH32(entry.timestamp, header.magic);
    entry.pid                        = NTOH32(entry.pid, header.magic);
    entry.tid                        = NTOH32(entry.tid, header.magic);
    entry.voluntary_ctxt_switches    = NTOH32(entry.voluntary_ctxt_switches, header.magic);
    entry.nonvoluntary_ctxt_switches = NTOH32(entry.nonvoluntary_ctxt_switches, header.magic);
    entry.cpu_migration              = NTOH32(entry.cpu_migration, header.magic);

    task_diff(&entry);

    snprintf(sqlbuf, sizeof(sqlbuf), TASK_INSERT_TABLE_SQL,
             i,
             entry.timestamp,
             entry.pid,
             entry.tid,
             entry.voluntary_ctxt_switches,
             entry.nonvoluntary_ctxt_switches,
             entry.cpu_migration);
    sqlite_exec(&g_tasksqlite, sqlbuf);
  }

  sqlite_close(&g_tasksqlite);
  close(fd);
  free_list();
  return 0;

fail:
  close(fd);
  sqlite_close(&g_tasksqlite);
  free_list();
  return -1;
}
