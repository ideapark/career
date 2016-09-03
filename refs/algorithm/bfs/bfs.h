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

static inline struct node *malloc_node(void)
{
	struct node *node = malloc(sizeof(struct node));
	INIT_LIST_HEAD(&node->list);
	return node;
}

static inline struct path *malloc_path(void)
{
	struct path *path = malloc(sizeof(struct path));
	INIT_LIST_HEAD(&path->link);
	INIT_LIST_HEAD(&path->list);
	return path;
}

static inline struct trace *malloc_trace(void)
{
	struct trace *trace = malloc(sizeof(struct trace));
	INIT_LIST_HEAD(&trace->link);
	INIT_LIST_HEAD(&trace->list);
	return trace;
}

static inline void free_nodelist(struct list_head *nodelist)
{
	struct list_head *pos, *n;
	list_for_each_safe(pos, n, nodelist) {
		list_del(pos);
		struct node *node = list_entry(pos, struct node, list);
		free(node);
	}
}

static inline void free_pathlist(struct list_head *pathlist)
{
	struct list_head *pos, *n;
	list_for_each_safe(pos, n, pathlist) {
		list_del(pos);
		struct path *path = list_entry(pos, struct path, link);
		free_nodelist(&path->list);
		free(path);
	}
}

static inline void free_tracelist(struct list_head *tracelist)
{
	struct list_head *pos, *n;
	list_for_each_safe(pos, n, tracelist) {
		list_del(pos);
		struct trace *trace = list_entry(pos, struct trace, link);
		free_nodelist(&trace->list);
		free(trace);
	}
}

/* pass predicate */
typedef int (*Pass)(const struct point *p);

/* target predicate */
typedef int (*Target)(const struct point *p);

int bfs(struct list_head *path, const struct point *start, Pass Pfn, Target Tfn);

#endif /* BFS_H */
