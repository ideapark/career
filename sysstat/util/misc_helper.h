/*
 * sysstat/util/misc_helper.h - some useful helpers
 *
 * Copyright (C) Zhou Peng <lockrecv@qq.com>
 */
#ifndef MISC_HELPER_H
#define MISC_HELPER_H

#include <stddef.h>
#include <inttypes.h>

#define SYMPATH_LEN  512
#define PROCEXE_LEN  64

/*
 * cpu_hz - get cpu hertz
 *
 * [result will be cached in static memory]
 */
float cpu_hz();

/*
 * cpu_cores - get cpu core numbers
 *
 * [result will be cached in static memory]
 */
int8_t cpu_cores();

enum space {
  SPACE_KERNEL,
  SPACE_USER,
};

/*
 * task_space - test process either kernel space or user psace task
 *
 * @arg pid: process id to test
 *
 * @ret SPACE_KERNEL  process is kernel space task
 *      SPACE_USER    process is user space task
 */
enum space task_space(int32_t pid);

/*
 * load_procfile - open the file specified by path, read 'size' bytes
 *                 to the 'buffer', then close the file (actually read
 *                 bytes maybe smaller than the requested size).
 */
int load_procfile(const char *path, char *buffer, size_t size);

/*
 * keycolon_sscanf - find the first occurrence of the 'key' in the 'str',
 *                   then find char ':' from that position, scans from the
 *                   place right after the ':' according to format.
 *
 * @arg key: the key to search (there must have a char ':' after the key and
 *           before the value read, THE KEY SHOULD NOT CONTAIN THE CHAR ':').
 * @arg str: original string to scanf.
 * @arg format: scanf format string.
 *
 * @ret: number of char succeed read.
 */
int keycolon_sscanf(const char *key, const char *str, const char *format, ...);

#endif /* MISC_HELPER_H */
