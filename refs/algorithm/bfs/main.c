/*
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#include <assert.h>
#include <stdio.h>

#include "list.h"
#include "bfs.h"

#define X_MAX 30
#define Y_MAX 30

#define BFS_GRAPH  "graph.txt"

#define GRAPH_GRASS    '+'
#define GRAPH_WALL     '#'
#define GRAPH_BOX      '$'
#define GRAPH_BOMB     '@'
#define GRAPH_PLAYER_A 'A'
#define GRAPH_PLAYER_B 'B'

char GRAPH[Y_MAX][X_MAX];
int GRAPH_Y;
int GRAPH_X;

static void load_graph(const char *graph)
{
	FILE *f = fopen(graph, "r");

	fscanf(f, "%d", &GRAPH_Y);
	fscanf(f, "%d", &GRAPH_X);

	assert(GRAPH_Y <= Y_MAX);
	assert(GRAPH_X <= X_MAX);

	for (int y = 0; y < GRAPH_Y; y++) {
		for (int x = 0; x < GRAPH_X; x++) {
			int ch;
			do {
				ch = fgetc(f);
				printf("%c", ch);
			} while (ch != EOF && ch == '\n');
			GRAPH[y][x] = (char)ch;
		}
	}
	printf("\n\n");

	fclose(f);
}

static int in_graph(const struct point *p)
{
	return p->x >= 0 && p->x < GRAPH_X &&
		p->y >= 0 && p->y < GRAPH_Y;
}

static int is_grass(const struct point *p)
{
	return in_graph(p) && (GRAPH[p->y][p->x] == GRAPH_GRASS);
}

static int is_wall(const struct point *p)
{
	return in_graph(p) && (GRAPH[p->y][p->x] == GRAPH_WALL);
}

static int is_box(const struct point *p)
{
	return in_graph(p) && (GRAPH[p->y][p->x] == GRAPH_BOX);
}

static int is_bomb(const struct point *p)
{
	return in_graph(p) && (GRAPH[p->y][p->x] == GRAPH_BOMB);
}

static int is_player_b(const struct point *p)
{
	return in_graph(p) && (GRAPH[p->y][p->x] == GRAPH_PLAYER_B);
}

static int can_cross(const struct point *p)
{
	return is_grass(p);
}

int print_node(struct list_head *node_head)
{
	int nrnode = 0;
	struct node *node;
	list_for_each_entry(node, node_head, list) {
		nrnode++;
		printf("(y:%d,x:%d)", node->p.y, node->p.x);
	}
	return nrnode;
}

int print_path(struct list_head *path_head)
{
	int nrpath = 0;
	struct path *path;
	list_for_each_entry(path, path_head, link) {
		nrpath++;
		print_node(&path->list);
		printf("\n");
	}
	return nrpath;
}

int main(int argc, char *argv[])
{
	load_graph(BFS_GRAPH);

	const struct point start = {.y=19, .x=0};

	int nr;
	struct list_head path_head;
	
	nr = bfs(&path_head, &start, can_cross, is_box);
	printf("box path: %d\n", nr);
	print_path(&path_head);

	nr = bfs(&path_head, &start, can_cross, is_wall);
	printf("wall path: %d\n", nr);
	print_path(&path_head);

	nr = bfs(&path_head, &start, can_cross, is_bomb);
	printf("bomb path: %d\n", nr);
	print_path(&path_head);

	nr = bfs(&path_head, &start, can_cross, is_player_b);
	printf("player B path: %d\n", nr);
	print_path(&path_head);

	return 0;
}
