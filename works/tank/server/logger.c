/*
 * logger.c
 *
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdarg.h>

#include "logger.h"

static FILE *log_stream= NULL;
static int tty_cache = 0;

static const char *strnow()
{
	static const char *timefmt = "[%Y-%m-%d %H:%M:%S]";
	static char buffer[32];

	time_t now;
	struct tm *timeinfo;

	time(&now);
	timeinfo = localtime(&now);
	strftime(buffer, 32, timefmt, timeinfo);
	return buffer;
}

static int logger(const char *color, const char *level,
		  const  char *fmt, va_list args)
{
	static const char *end = "\e[00m";

	int cnt = 0;

	if (!log_stream)
		return cnt;

	if (tty_cache)
		cnt += fprintf(log_stream, color);
	cnt += fprintf(log_stream, strnow());
	cnt += fprintf(log_stream, level);
	cnt += vfprintf(log_stream, fmt, args);
	if (tty_cache)
		cnt += fprintf(log_stream, end);
	return cnt;
}

void logger_setlog(FILE *stream)
{
	int fd = fileno(stream);
	tty_cache = isatty(fd);
	log_stream = stream;
}

int logger_info(const char *fmt, ...)
{
	static const char *blue = "\e[00;36m";
	static const char *info = "[info] ";

	int cnt;
	va_list args;

	va_start(args, fmt);
	cnt = logger(blue, info, fmt, args);
	va_end(args);

	return cnt;
}

int logger_warning(const char *fmt, ...)
{
	static const char *red = "\e[00;33m";
	static const char *warning = "[warning] ";

	int cnt;
	va_list args;

	va_start(args, fmt);
	cnt = logger(red, warning, fmt, args);
	va_end(args);

	return cnt;
}

int logger_error(const char *fmt, ...)
{
	static const char *red = "\e[00;31m";
	static const char *error = "[error] ";

	int cnt;
	va_list args;

	va_start(args, fmt);
	cnt = logger(red, error, fmt, args);
	va_end(args);

	return cnt;
}
