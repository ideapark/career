/*
 * sysstat/core/main.h - sysstat type defines
 *
 * Copyright (C) Zhou Peng <lockrecv@gmail.com>
 */
#ifndef SYSSTAT_MAIN_H
#define SYSSTAT_MAIN_H

#include <stdint.h>

#define SAMPLECNT_MAX       0x1fffffff
#define CALLBACKQUEUE_LEN   5

typedef void (*init_t)(void);
typedef void (*run_t)(void);
typedef void (*exit_t)(void);

typedef struct {
    init_t  init;  /* called when process begin to execute */
    run_t   run;   /* called each alarm signal */
    exit_t  exit;  /* called before process exit */
} callback_t;

typedef enum {
    untaken = 0,
    taken   = 1,
} taken_t;

typedef struct {
    callback_t callback;
    taken_t    taken;
} queue_entry;

/*
 * current timestamp
 */
extern long g_timestamp;

/*
 * register/unregister call back
 */
int register_callback(const callback_t *callback);
void unregister_callback(int i);

typedef int (*parser_t)(const char *datafile, const char *dbname);

typedef struct {
    const char *file;
    parser_t   parser;
    taken_t    taken;
} parser_entry;

#endif /* SYSSTAT_MAIN_H */
