/*
 * sysstat/util/misc_helper.c - some useful helpers
 *
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#include <unistd.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "util/misc_helper.h"

float cpu_hz()
{
	static float hz = 0;
	FILE *fp;
	char *line = NULL;
	size_t len;

	if (hz == 0) {
		if (access("/proc/cpuinfo", F_OK) == -1)
			goto fail;
		if ((fp = fopen("/proc/cpuinfo", "r")) == NULL)
			goto fail;
		while (getline(&line, &len, fp) != -1) {
			if (memcmp(line, "cpu MHz", 7) == 0) {
				sscanf(line, "%*s %*s %*s %f", &hz);
				break;
			}
		}
		free(line);
		fclose(fp);
	}
	return hz;

fail:
	fprintf(stderr, "read cpu hertz failed.\n");
	return 0;
}

int8_t cpu_cores()
{
	static int8_t cores = 0;

	FILE *fp;
	char *line = NULL;
	size_t len;

	if (cores == 0) {
		if (access("/proc/cpuinfo", F_OK) == -1)
			goto fail;
		if ((fp = fopen("/proc/cpuinfo", "r")) == NULL)
			goto fail;
		while (getline(&line, &len, fp) != -1) {
			if (memcmp(line, "processor", 9) == 0)
				cores++;
		}
		if (line)
			free(line);
		fclose(fp);
	}
	return cores;

fail:
	fprintf(stderr, "read cpu core numbers failed.\n");
	return 0;
}

enum space task_space(int32_t pid)
{
	ssize_t r;
	char linkfile[SYMPATH_LEN] = {'\0'};
	char exepath[PROCEXE_LEN] = {'\0'};

	snprintf(exepath, PROCEXE_LEN, "/proc/%d/exe", pid);

	if ((r = readlink(exepath, linkfile, SYMPATH_LEN)) == -1)
		goto out;

	linkfile[r] = '\0';

	/*
	 * this process has an executable image on
	 * disk, so we treat it as user space task
	 */
	if (access(linkfile, F_OK) != -1)
		return SPACE_USER;

out:
	return SPACE_KERNEL;
}

int load_procfile(const char *path, char *buffer, size_t size)
{
	int fd, nr;

	if ((fd = open(path, O_RDONLY, 0644)) < 0)
		goto out;

	if ((nr = read(fd, buffer, size)) >= 0)
		buffer[nr] = '\0';

	close(fd);
	return 0;

out:
	fprintf(stderr, "load_procfile failed: %s.\n", path);
	return -1;
}

int keycolon_sscanf(const char *key, const char *str, const char *format, ...)
{
	char *keypos, *colonpos;
	va_list ap;
	int nscan;

	if ((keypos = strstr(str, key)) != NULL && (colonpos = strstr(keypos, ":")) != NULL) {
		va_start(ap, format);
		nscan = vsscanf(colonpos + 1, format, ap);
		return nscan;
	} else {
		return -1;
	}
}
