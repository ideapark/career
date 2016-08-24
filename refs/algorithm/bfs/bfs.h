/*
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#ifndef BFS_H
#define BFS_H

#include "point.h"

#include <list>

typedef bool (*PathAssert)(const struct point &p);
typedef bool (*FoundAssert)(const struct point &p);


void bfs_search_all(const struct point start,
		std::list<std::list<struct point> > &all_path,
		PathAssert PA, FoundAssert FA);

#endif /* BFS_H */
