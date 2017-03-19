/*
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#ifndef BFS_H
#define BFS_H

#include <stdio.h>
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
	struct list_head list;
	struct list_head node;
};

struct trace {
	struct point p;
	struct list_head list;
	struct list_head node;
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
	INIT_LIST_HEAD(&path->list);
	INIT_LIST_HEAD(&path->node);
	return path;
}

static inline struct trace *malloc_trace(void)
{
	struct trace *trace = malloc(sizeof(struct trace));
	INIT_LIST_HEAD(&trace->list);
	INIT_LIST_HEAD(&trace->node);
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
		struct path *path = list_entry(pos, struct path, list);
		free_nodelist(&path->node);
		free(path);
	}
}

static inline void free_tracelist(struct list_head *tracelist)
{
	struct list_head *pos, *n;
	list_for_each_safe(pos, n, tracelist) {
		list_del(pos);
		struct trace *trace = list_entry(pos, struct trace, list);
		free_nodelist(&trace->node);
		free(trace);
	}
}

static inline int PRINT(struct list_head *nodelist)
{
	int nrnode = 0;
	struct node *node;
	list_for_each_entry(node, nodelist, list) {
		nrnode++;
		printf("(%d,%d)", node->p.y, node->p.x);
	}
	printf("\n");
	return nrnode;
}

/* pass predicate */
typedef int (*Pass)(const struct point *p);

/* target predicate */
typedef int (*Target)(const struct point *p);

/*
 * @pathlist each node contains a list of point to the target
 * @start search start point
 * @Pfn assert point can be passed through
 * @Tfn assert point is the target point
 */
int bfs_path(struct list_head *pathlist, const struct point *start,
	     Pass Pfn, Target Tfn);

#endif /* BFS_H */
