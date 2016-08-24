/*
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#ifndef POINT_H
#define POINT_H

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

#endif /* POINT_H */
