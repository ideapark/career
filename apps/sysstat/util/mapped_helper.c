/*
 * sysstat/util/mapped_helper.c - Linux mapped memory file I/O
 *
 * Copyright (c) Zhou Peng <p@ctriple.cn>
 */

#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include <stdio.h>
#include <string.h>

#include "core/config.h"
#include "util/mapped_helper.h"

/*
 * open file and mapped to memory
 */
int mapped_open(mapfile_t *mapfile, const char *filename)
{
	struct stat statbuf;

	mapfile->page_size = getpagesize() * MAPPED_PAGES;

	if (access(filename, F_OK) != -1) {
		fprintf(stderr, "removing: %s\n", filename);
		if (remove(filename) != 0) {
			fprintf(stderr, "remove file failed: %s\n", filename);
			goto out;
		}
	}
	if ((mapfile->fd = open(filename, O_CREAT|O_RDWR, 0644)) < 0) {
		fprintf(stderr, "create file failed: %s\n", filename);
		goto out;
	}

	if (fstat(mapfile->fd, &statbuf) != 0) {
		fprintf(stderr, "stat file failed: %s\n", filename);
		goto fail;
	}
	if (statbuf.st_size != 0) {
		fprintf(stderr, "file is not empty: %s\n", filename);
		goto fail;
	}
	if (ftruncate(mapfile->fd, mapfile->page_size)) {
		fprintf(stderr, "increase file size failed: %s", filename);
		goto fail;
	}

	mapfile->addr = mmap(0, mapfile->page_size, PROT_READ|PROT_WRITE,
			     MAP_SHARED, mapfile->fd, 0);

	if (mapfile->addr == MAP_FAILED) {
		fprintf(stderr, "mmap file failed: %s\n", filename);
		goto fail;
	}

	mapfile->used_size = 0;
	return 0;

fail:
	close(mapfile->fd);
	goto out;

out:
	return -1;
}

/*
 * write data to mapped file
 */
int mapped_write(mapfile_t *mapfile, const void *data, size_t size)
{
	size_t prev_size;
	size_t next_size;
	struct stat stat;

	if (size + mapfile->used_size < mapfile->page_size) {
		memcpy(mapfile->addr + mapfile->used_size, data, size);
		mapfile->used_size += size;
		return 0;
	}

	/*
	 * write to disk and map next block
	 */

	prev_size = mapfile->page_size - mapfile->used_size;
	next_size = size - prev_size;

	memcpy(mapfile->addr + mapfile->used_size, data, prev_size);

	if (msync(mapfile->addr, mapfile->page_size, MS_ASYNC) == -1) {
		fprintf(stderr, "mapped_write msync failed!\n");
		return -1;
	}
	if (munmap(mapfile->addr, mapfile->page_size) == -1) {
		fprintf(stderr, "mapped_write munmap failed!\n");
		return -1;
	}

	mapfile->used_size = mapfile->page_size;

	if (fstat(mapfile->fd, &stat) != 0) {
		fprintf(stderr, "mapped_write stat file failed!\n");
		return -1;
	}

	if (ftruncate(mapfile->fd, stat.st_size + mapfile->page_size) != 0) {
		fprintf(stderr, "mapped_write increase file failed!\n");
		return -1;
	}

	mapfile->addr = mmap(0, mapfile->page_size, PROT_READ|PROT_WRITE,
			     MAP_SHARED, mapfile->fd, stat.st_size);

	if (mapfile->addr == MAP_FAILED) {
		fprintf(stderr, "mapped_grow remmap failed!\n");
		return -1;
	}

	memcpy(mapfile->addr, data + prev_size, next_size);
	mapfile->used_size = next_size;

	return 0;
}

/*
 * close mapped file and synchronize data to disk
 */
int mapped_close(mapfile_t *mapfile)
{
	int remain_size;
	struct stat stat;

	msync(mapfile->addr, mapfile->page_size, MS_ASYNC);
	munmap(mapfile->addr, mapfile->page_size);

	if (fstat(mapfile->fd, &stat) != 0) {
		fprintf(stderr, "mapped_close stat file failed!\n");
		return -1;
	}

	remain_size = mapfile->page_size-mapfile->used_size;

	if (ftruncate(mapfile->fd, stat.st_size - remain_size) != 0) {
		fprintf(stderr, "mapped_close decrease file failed!\n");
		return -1;
	}
	close(mapfile->fd);

	mapfile->fd = -1;
	mapfile->addr = NULL;
	mapfile->page_size = 0;
	mapfile->used_size = 0xffffffff;

	return 0;
}
