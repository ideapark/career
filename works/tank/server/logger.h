#ifndef LOGER_H
#define LOGER_H

#include <stdio.h>

void logger_setlog(FILE *stream);
int logger_info(const char *fmt, ...);
int logger_warning(const char *fmt, ...);
int logger_error(const char *fmt, ...);

#endif /* LOGER_H */
