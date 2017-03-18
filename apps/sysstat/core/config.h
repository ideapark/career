/*
 * sysstat/core/config.h - sysstat macro defines and constants
 *
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#ifndef SYSSTAT_CONFIG_H
#define SYSSTAT_CONFIG_H

#define SYSSTAT_MAGIC           0x4441450a
#define DEFAULT_INTERVAL        1
#define SQL_BUFSIZE             2048
#define PROCFILE_BUFSIZE        4096

#define IRQ_SAMPLEFILE          "irq.data"
#define SYS_SAMPLEFILE          "sys.data"
#define VM_SAMPLEFILE           "vm.data"
#define TASK_SAMPLEFILE         "task.data"

#endif /* SYSSTAT_CONFIG_H */
