/*
 * map.c
 *
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#include <assert.h>
#include <stdio.h>

#include "map.h"
#include "logger.h"

static char MAP[Y_MAX][X_MAX] = {{AREA}};

static void map_print(void)
{
	short y, x;
	for (y = 0; y < Y_MAX; y++) {
		char line[X_MAX+1] = {'\0'};
		for (x = 0; x < X_MAX; x++)
			line[x] = MAP[y][x];
		logger_info("%s\n", line);
	}
}

int map_load(const char *map)
{
	FILE *f = fopen(map, "r");
	if (!f) {
		logger_error("%s\n", "map file open failed.");
		return 0;
	}

	short map_y, map_x;
	fscanf(f, "%hi", &map_y);
	fscanf(f, "%hi", &map_x);
	if (map_y != Y_MAX || map_x != X_MAX) {
		logger_error("%s\n", "map Y or X does NOT match expected.");
		fclose(f);
		return 0;
	}

	short y, x;
	char ch;
	int cnt;
	for (y = 0; y < map_y; y++) {
		for (x = 0; x < map_x; x++) {
			do {
				cnt = fscanf(f, "%c", &ch);
			} while (cnt == 1 && ch == '\n');
			if (cnt == 1)
				MAP[y][x] = ch;
			else {
				logger_error("%s\n", "map content incomplete.");
				fclose(f);
				return 0;
			}
		}
	}
	fclose(f);
	map_print();
	return 1;
}

char map_get(short y, short x)
{
	assert(y >= 0 && y < Y_MAX && x >= 0 && x < X_MAX);
	return MAP[y][x];
}

char map_set(short y, short x, char ch)
{
	assert(y >= 0 && y < Y_MAX && x >= 0 && x < X_MAX);
	char old = MAP[y][x];
	MAP[y][x] = ch;
	return old;
}
