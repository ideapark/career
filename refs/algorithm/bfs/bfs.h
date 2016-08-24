/*
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#ifndef BFS_H
#define BFS_H

#include "list.h"
#include "point.h"

/* node of one path */
struct node {
	struct point p;
	struct list_head list;
};

/* path from start to target */
struct path {
	struct list_head path;
	struct list_head list;
};

/*
 * test if point can pass
 */
typedef int (*Pass)(const struct point *p);

/*
 * test if point is target
 */
typedef int (*Target)(const struct point *p);

/*
 * @desc
 *           breadth first search algorithm
 *
 * @arg path
 *           path list head
 * @arg start
 *           search start point
 * @arg Pfn
 *           function tests if point can be passed
 * @arg Tfn
 *           function tests if point is target
 * @ret int
 *           path number found
 */
int bfs(struct list_head *path, const struct point *start, Pass Pfn, Target Tfn);

#endif /* BFS_H */
