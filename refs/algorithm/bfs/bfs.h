/*
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#ifndef BFS_H
#define BFS_H

#include "list.h"

struct point {
	short y;
	short x;
};

static inline struct point UP(const struct point *p)
{
	struct point up;

	up.x = p->x;
	up.y = p->y - 1;

	return up;
}

static inline struct point DOWN(const struct point *p)
{
	struct point down;

	down.x = p->x;
	down.y = p->y + 1;

	return down;
}

static inline struct point LEFT(const struct point *p)
{
	struct point left;

	left.x = p->x - 1;
	left.y = p->y;

	return left;
}

static inline struct point RIGHT(const struct point *p)
{
	struct point right;

	right.x = p->x + 1;
	right.y = p->y;

	return right;
}

/* node of path */
struct node {
	struct point p;
	struct list_head list;
};

/* one path start to target */
struct path {
	struct list_head path;
	struct list_head list;
};

/* pass predicate */
typedef int (*Pass)(const struct point *p);

/* target predicate */
typedef int (*Target)(const struct point *p);

int bfs(struct list_head *path, const struct point *start, Pass Pfn, Target Tfn);

#endif /* BFS_H */
