/*
 * sysstat/task/task.c - sysstat task sample
 *
 * Copyright (C) Zhou Peng <lockrecv@qq.com>
 */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "core/config.h"
#include "core/main.h"
#include "task/task.h"
#include "util/misc_helper.h"
#include "util/mapped_helper.h"

static mapfile_t g_taskfile;
static task_header g_header;

static char *g_buffer;

static int task_readstatus(const char *status, task_entry *entry)
{
  if (load_procfile(status, g_buffer, PROCFILE_BUFSIZE) < 0)
    return -1;

  keycolon_sscanf("voluntary_ctxt_switches", g_buffer, "%"SCNd32,
                  &entry->voluntary_ctxt_switches);
  keycolon_sscanf("nonvoluntary_ctxt_switches", g_buffer, "%"SCNd32,
                  &entry->nonvoluntary_ctxt_switches);

  return 0;
}

static int task_readsched(const char *sched, task_entry *entry)
{
  if (load_procfile(sched, g_buffer, PROCFILE_BUFSIZE) < 0)
    return -1;

  keycolon_sscanf("se.nr_migrations", g_buffer, "%"SCNd32,
                  &entry->cpu_migration);

  return 0;
}

static int task_snapshot(task_header *header)
{
  DIR *proc_dir, *task_dir;
  struct dirent *proc_ent, *task_ent;
  char path[TASKPATH_MAX];

  /* initialized task entry */
  task_entry entry = {
    .timestamp                  = 0,
    .pid                        = 0,
    .tid                        = 0,
    .voluntary_ctxt_switches    = 0,
    .nonvoluntary_ctxt_switches = 0,
    .cpu_migration              = 0,
  };

  if ((proc_dir = opendir("/proc")) == NULL) {
    fprintf(stderr, "task_snapshot: open /proc failed.\n");
    return -1;
  }

  /*
   * for each user space process
   */
  while ((proc_ent = readdir(proc_dir)) != NULL) {
    if (!isdigit((int)proc_ent->d_name[0]) || proc_ent->d_type != DT_DIR)
      continue;

    if (task_space(atoi(proc_ent->d_name)) == SPACE_KERNEL)
      continue;

    snprintf(path, TASKPATH_MAX, "/proc/%s/task", proc_ent->d_name);

    if (access(path, F_OK) != 0) {
      fprintf(stderr, "task_snapshot: process has no thread.\n");
      continue;
    }

    if ((task_dir = opendir(path)) == NULL) {
      fprintf(stderr, "task_snapshot: open %s failed.\n", path);
      continue;
    }

    /*
     * for each task
     */
    while ((task_ent = readdir(task_dir)) != NULL) {
      if (!isdigit((int)task_ent->d_name[0]) || task_ent->d_type != DT_DIR)
        continue;

      entry.timestamp = g_timestamp;
      sscanf(proc_ent->d_name, "%"SCNu32, &entry.pid);
      sscanf(task_ent->d_name, "%"SCNu32, &entry.tid);

      snprintf(path, TASKPATH_MAX, "/proc/%s/task/%s/status",
               proc_ent->d_name, task_ent->d_name);
      task_readstatus(path, &entry);

      snprintf(path, TASKPATH_MAX, "/proc/%s/task/%s/sched",
               proc_ent->d_name, task_ent->d_name);
      task_readsched(path, &entry);

      mapped_write(&g_taskfile, (void *)&entry, sizeof(entry));
      header->count++;
    }
    closedir(task_dir);
  }
  closedir(proc_dir);
  return 0;
}

static int write_taskheader(task_header *header)
{
  int fd;

  if ((fd = open(TASK_SAMPLEFILE, O_RDWR, 0644)) == -1)
    goto fail;

  if (write(fd, header, sizeof(*header)) != sizeof(*header))
    fprintf(stderr, "task write_header failed.\n");
  close(fd);

  return 0;

fail:
  fprintf(stderr, "write task sample file header failed.\n");
  return -1;
}

/*
 * @brief: thread info sample initialization
 */
void task_init(void)
{
  g_header.magic = SYSSTAT_MAGIC;
  g_header.count = 0;

  mapped_open(&g_taskfile, TASK_SAMPLEFILE);
  mapped_write(&g_taskfile, &g_header, sizeof(g_header));

  if ((g_buffer = (char *)malloc(PROCFILE_BUFSIZE)) == NULL) {
    fprintf(stderr, "task_init failed.\n");
    exit(-1);
  }
}

/*
 * @brief: thread info take one snapshot
 */
void task_run(void)
{
  task_snapshot(&g_header);
}

/*
 * @brief: finish thread info sample, close mapped file and write task_header
 */
void task_exit(void)
{
  mapped_close(&g_taskfile);
  write_taskheader(&g_header);
  free(g_buffer);
}
