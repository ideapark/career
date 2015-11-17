/*
 * sysstat/proc/proc.c - sysstat process sample
 *
 * Copyright (C) Zhou Peng <lockrecv@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

#include "core/config.h"
#include "core/main.h"
#include "proc/proc.h"
#include "util/misc_helper.h"
#include "util/mapped_helper.h"

static mapfile_t g_procfile;
static proc_header g_header;

static char *g_buffer;

static int proc_nameidx(proc_header *header, const char *name)
{
    short i;

    for (i = 0; i < PROC_NR; i++) {
        if (header->proc_names[i][0] == '\0')
            strncpy(&header->proc_names[i][0], name, PROC_NAMELEN);
        if (strncmp(name, &header->proc_names[i][0], PROC_NAMELEN) == 0)
            return i;
    }
    return -1;
}

static int proc_readstatus(const char *status, proc_entry *entry)
{
    char namebuf[PROC_NAMELEN];

    if (load_procfile(status, g_buffer, PROCFILE_BUFSIZE) < 0)
        return -1;

    keycolon_sscanf("VmPeak", g_buffer, "%"SCNd32, &entry->mem.vm_peak);
    keycolon_sscanf("VmSize", g_buffer, "%"SCNd32, &entry->mem.vm_size);
    keycolon_sscanf("VmLck",  g_buffer, "%"SCNd32, &entry->mem.vm_lck);
    keycolon_sscanf("VmHWM",  g_buffer, "%"SCNd32, &entry->mem.vm_hwm);
    keycolon_sscanf("VmRSS",  g_buffer, "%"SCNd32, &entry->mem.vm_rss);
    keycolon_sscanf("VmData", g_buffer, "%"SCNd32, &entry->mem.vm_data);
    keycolon_sscanf("VmStk",  g_buffer, "%"SCNd32, &entry->mem.vm_stk);
    keycolon_sscanf("VmExe",  g_buffer, "%"SCNd32, &entry->mem.vm_exe);
    keycolon_sscanf("VmLib",  g_buffer, "%"SCNd32, &entry->mem.vm_lib);
    keycolon_sscanf("VmPTE",  g_buffer, "%"SCNd32, &entry->mem.vm_pte);
    keycolon_sscanf("Stack usage", g_buffer, "%"SCNd32, &entry->mem.stack_usage);

    keycolon_sscanf("voluntary_ctxt_switches", g_buffer, "%"SCNd32,
                    &entry->ctx.voluntary_ctxt_switch);
    keycolon_sscanf("nonvoluntary_ctxt_switches", g_buffer, "%"SCNd32,
                    &entry->ctx.novoluntary_ctxt_switch);

    keycolon_sscanf("Pid", g_buffer, "%"SCNd32, &entry->pid);
    keycolon_sscanf("Name", g_buffer, "%s", namebuf);
    entry->name_idx = proc_nameidx(&g_header, namebuf);

    return 0;
}

static int proc_snapshot(proc_header *header)
{
    DIR *proc_dir;
    struct dirent *proc_ent;
    char path[PROC_PATHMAX];

    /* initialized process entry */
    proc_entry entry = {
        .timestamp = 0,
        .pid       = 0,
        .name_idx  = 0,
        .mem = {
            .vm_peak = 0,
            .vm_size = 0,
            .vm_lck  = 0,
            .vm_hwm  = 0,
            .vm_rss  = 0,
            .vm_data = 0,
            .vm_stk  = 0,
            .vm_exe  = 0,
            .vm_lib  = 0,
            .vm_pte  = 0,
            .stack_usage = 0,
        },
        .ctx = {
            .voluntary_ctxt_switch   = 0,
            .novoluntary_ctxt_switch = 0,
        },
    };

    if ((proc_dir = opendir("/proc")) == NULL) {
        fprintf(stderr, "proc_snapshot: open /proc failed.\n");
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

        snprintf(path, PROC_PATHMAX, "/proc/%s/status", proc_ent->d_name);

        entry.timestamp = g_timestamp;
        proc_readstatus(path, &entry);
        mapped_write(&g_procfile, (void *)&entry, sizeof(entry));
        header->count++;
    }
    closedir(proc_dir);
    return 0;
}

static int write_procheader(proc_header *header)
{
    int fd;

    if ((fd = open(PROC_SAMPLEFILE, O_RDWR, 0644)) == -1)
        goto fail;

    if (write(fd, header, sizeof(*header)) < 0)
        fprintf(stderr, "process write_header failed.\n");
    close(fd);

    return 0;

fail:
    fprintf(stderr, "write process sample file header failed.\n");
    return -1;
}

/*
 * @brief: process sample module initialization
 */
void proc_init(void)
{
    int i;

    g_header.magic = SYSSTAT_MAGIC;
    g_header.count = 0;

    for (i = 0; i < PROC_NR; i++)
        memset(&g_header.proc_names[i][0], '\0', PROC_NAMELEN);

    mapped_open(&g_procfile, PROC_SAMPLEFILE);
    mapped_write(&g_procfile, &g_header, sizeof(g_header));

    if ((g_buffer = (char *)malloc(PROCFILE_BUFSIZE)) == NULL) {
        fprintf(stderr, "proc_init failed.\n");
        exit(-1);
    }
}

/*
 * @brief: process sample module take one snapshot
 */
void proc_run(void)
{
    proc_snapshot(&g_header);
}

/*
 * @brief: finish process sample, close mapped file and write proc_header
 */
void proc_exit(void)
{
    mapped_close(&g_procfile);
    write_procheader(&g_header);
    free(g_buffer);
}
