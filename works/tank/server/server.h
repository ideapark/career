/*
 * server.h
 *
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#ifndef SERVER_H
#define SERVER_H

/* game limits */
#define TANK_MAX    4
#define LIFE_MAX    4
#define LEG_MAX     2
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

struct postion {
	short y;
	short x;
};

struct tank {
	short id;
	short star_count;
	struct postion pos;
};

struct team {
	short id;
	char name[NAME_MAX];
	struct tank tanks[TANK_MAX];

	int life_remain;
};

struct game {
	int leg_remain;
	int round_remain;
	struct team teams[TEAM_MAX];
};

#endif /* SERVER_H */
