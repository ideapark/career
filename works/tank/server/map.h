/*
 * map.h
 *
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#ifndef MAP_H
#define MAP_H

#include "cJSON.h"

/* map limits */
#define Y_MAX 15
#define X_MAX 15

/* map point */
#define BRICK '#'
#define IRON  '@'
#define RIVER '~'
#define COIN1 '1'
#define COIN2 '2'
#define COIN3 '3'
#define COIN4 '4'
#define COIN5 '5'
#define STAR  '*'
#define AREA  '-'
#define TANK  '!'

/*
 * read map from  file
 */
int map_load(const char *map);

/*
 * get map point
 */
char map_get(short y, short x);

/*
 * set map point, return old point
 */
char map_set(short y, short x, char ch);

/*
 * map serialized to json
 */
cJSON *map_json(void);

#endif /* MAP_H */
