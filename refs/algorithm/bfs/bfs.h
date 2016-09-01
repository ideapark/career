/*
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#ifndef BFS_H
#define BFS_H

#include <stdlib.h>

#include "list.h"

struct point {
	short y;
	short x;
};

static inline struct point U(const struct point *p)
{
	struct point up;

	up.x = p->x;
	up.y = p->y - 1;

	return up;
}

static inline struct point D(const struct point *p)
{
	struct point down;

	down.x = p->x;
	down.y = p->y + 1;

	return down;
}

static inline struct point L(const struct point *p)
{
	struct point left;

	left.x = p->x - 1;
	left.y = p->y;

	return left;
}

static inline struct point R(const struct point *p)
{
	struct point right;

	right.x = p->x + 1;
	right.y = p->y;

	return right;
}

static inline int EQ(const struct point *p1, const struct point *p2)
{
	return (p1->x == p2->x) && (p1->y == p2->y);
}

struct node {
	struct point p;
	struct list_head list;
};

struct path {
	struct list_head link;
	struct list_head list;
};

struct trace {
	struct point p;
	struct list_head link;
	struct list_head list;
};

static inline struct node *new_node(void)
{
	struct node *node = malloc(sizeof(struct node));
	INIT_LIST_HEAD(&node->list);
	return node;
}

static inline struct path *new_path(void)
{
	struct node *path = malloc(sizeof(struct path));
	INIT_LIST_HEAD(&path->link);
	INIT_LIST_HEAD(&path->list);
	return path;
}

static inline struct trace *new_trace(void)
{
	struct trace *trace = malloc(sizeof(struct trace));
	INIT_LIST_HEAD(&trace->link);
	INIT_LIST_HEAD(&trace->list);
	return trace;
}

/* pass predicate */
typedef int (*Pass)(const struct point *p);

/* target predicate */
typedef int (*Target)(const struct point *p);

int bfs(struct list_head *path, const struct point *start, Pass Pfn, Target Tfn);

#endif /* BFS_H */
