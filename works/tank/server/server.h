/*
 * server.h
 *
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#ifndef SERVER_H
#define SERVER_H

#include "list.h"

/* game limits */
#define TANK_MAX    4
#define LIFE_MAX    4
#define LEG_MAX     2
#define STAR_MAX    1
#define ROUND_MAX   150
#define TEAM_MAX    2
#define NAME_MAX    16
#define OFFLINE_MAX 10

enum direction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	STILL
};

struct position {
	short y;
	short x;
};

struct star {
	enum direction dir;
	struct position pos;
	struct list_head list;
};

struct bullet {
	enum direction dir;
	struct position pos;
	struct list_head list;
};

struct tank {
	short id;
	short star_count;
	struct position pos;
};

struct team {
	short id;
	int sockfd;
	char name[NAME_MAX];
	int life_remain;
	struct tank tanks[TANK_MAX];
	struct list_head stars;
	struct list_head bullets;
};

struct game {
	int leg_remain;
	int round_remain;
	struct team teams[TEAM_MAX];
};

#endif /* SERVER_H */
