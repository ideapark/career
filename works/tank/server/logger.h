/*
 * logger.h
 *
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

int logger_open(const char *logfile);
int logger_close();
int logger_info(const char *fmt, ...);
int logger_warning(const char *fmt, ...);
int logger_error(const char *fmt, ...);

#endif /* LOGGER_H */
