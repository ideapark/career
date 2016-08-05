/*
 * map.h
 *
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#ifndef MAP_H
#define MAP_H

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

int map_load(const char *map);

#endif /* MAP_H */
