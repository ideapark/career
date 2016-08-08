/*
 * logger.h
 *
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

/*
 * setup logger
 */
int logger_open(const char *logfile);

/*
 * close logger
 */
int logger_close();

/*
 * info level log
 * return letter count
 */
int logger_info(const char *fmt, ...);

/*
 * warn level log
 * return letter count
 */
int logger_warn(const char *fmt, ...);

/*
 * error level log
 * return letter count
 */
int logger_error(const char *fmt, ...);

#endif /* LOGGER_H */
