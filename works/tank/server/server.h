/*
 * server.h
 *
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#ifndef SERVER_H
#define SERVER_H

#include <string.h>

#include "list.h"

/* game limits */
#define TANK_MAX    4
#define LIFE_MAX    4
#define LEG_MAX     2
#define STAR_MAX    1
#define ROUND_MAX   150
#define TEAM_MAX    2
#define NAME_MAX    16
#define BUFFER_MAX  2048
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
	char name[NAME_MAX+1];
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

static inline const char *dir2str(enum direction dir)
{
	switch (dir) {
	case UP:
		return "up";
	case DOWN:
		return "down";
	case LEFT:
		return "left";
	case RIGHT:
		return "right";
	default:
		return "";
	}
}

static inline enum direction str2dir(const char *str)
{
	if (strcmp(str, "up") == 0)
		return UP;
	else if (strcmp(str, "down") == 0)
		return DOWN;
	else if (strcmp(str, "left") == 0)
		return LEFT;
	else if (strcmp(str, "right") == 0)
		return RIGHT;
	else
		return STILL;
}

#endif /* SERVER_H */
