/*
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#include <assert.h>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "bfs_config.h"
#include "bfs_impl.h"
#include "bfs_point.h"

#define BFS_GRAPH_X  30
#define BFS_GRAPH_Y  30

#define BFS_GRAPH_GRASS    '+'
#define BFS_GRAPH_WALL     '#'
#define BFS_GRAPH_BOX      '$'
#define BFS_GRAPH_BOMB     '@'
#define BFS_GRAPH_PLAYER_A 'A'
#define BFS_GRAPH_PLAYER_B 'B'

char bfs_graph[BFS_GRAPH_Y][BFS_GRAPH_X];
int bfs_graph_y;
int bfs_graph_x;


static void load_graph(const char *graph)
{
	std::ifstream in(graph, std::ios::in);

	in >> bfs_graph_y;
	in >> bfs_graph_x;

	assert(bfs_graph_y <= BFS_GRAPH_Y);
	assert(bfs_graph_x <= BFS_GRAPH_X);

	for (int y = 0; y < bfs_graph_y; y++) {
		for (int x = 0; x < bfs_graph_x; x++) {
			char ch;
			do {
				ch = in.get();
#if BFS_DEBUG
				std::cout << ch;
#endif
			} while (ch != EOF && ch == '\n');
			bfs_graph[y][x] = ch;
		}
	}

	in.close();
}

static bool in_graph(const struct point &p)
{
	return p.x >= 0 && p.x < bfs_graph_x &&
		p.y >= 0 && p.y < bfs_graph_y;
}

static bool is_grass(const struct point &p)
{
	return in_graph(p) && (bfs_graph[p.y][p.x] == BFS_GRAPH_GRASS);
}

static bool is_wall(const struct point &p)
{
	return in_graph(p) && (bfs_graph[p.y][p.x] == BFS_GRAPH_WALL);
}

static bool is_box(const struct point &p)
{
	return in_graph(p) && (bfs_graph[p.y][p.x] == BFS_GRAPH_BOX);
}

static bool is_bomb(const struct point &p)
{
	return in_graph(p) && (bfs_graph[p.y][p.x] == BFS_GRAPH_BOMB);
}

static bool is_player_b(const struct point &p)
{
	return in_graph(p) && (bfs_graph[p.y][p.x] == BFS_GRAPH_PLAYER_B);
}

static bool can_cross(const struct point &p)
{
	return is_grass(p);
}

struct PrintPoint
{
	void operator()(const struct point &p) {
		std::cout << "(" << p.x << "," << p.y << ")";
	}
};

struct PrintPath
{
	void operator()(const std::list<struct point> &path) {
		std::for_each(path.begin(), path.end(), PrintPoint());
		std::cout << std::endl;
	}
};

int main(int argc, char *argv[])
{
	load_graph(BFS_GRAPH);

	std::cout << std::endl << std::endl;

	const struct point start = {.x=10, .y=10};

	std::list<std::list<struct point> > box_pathes;
	bfs_search_all(start, box_pathes, can_cross, is_box);
	std::cout << "box path: " << box_pathes.size() << std::endl;
	std::for_each(box_pathes.begin(), box_pathes.end(), PrintPath());
	std::cout << std::endl;

	std::list<std::list<struct point> > wall_pathes;
	bfs_search_all(start, wall_pathes, can_cross, is_wall);
	std::cout << "wall path: " << wall_pathes.size() << std::endl;
	std::for_each(wall_pathes.begin(), wall_pathes.end(), PrintPath());
	std::cout << std::endl;

	std::list<std::list<struct point> > bomb_pathes;
	bfs_search_all(start, bomb_pathes, can_cross, is_bomb);
	std::cout << "bomb path: " << bomb_pathes.size() << std::endl;
	std::for_each(bomb_pathes.begin(), bomb_pathes.end(), PrintPath());
	std::cout << std::endl;

	std::list<std::list<struct point> > player_pathes;
	bfs_search_all(start, player_pathes, can_cross, is_player_b);
	std::cout << "player B path: " << player_pathes.size() << std::endl;
	std::for_each(player_pathes.begin(), player_pathes.end(), PrintPath());
	std::cout << std::endl;

	return 0;
}
