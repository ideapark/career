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

	int ch;

	for (int y = 0; y < GRAPH_Y; y++) {
		for (int x = 0; x < GRAPH_X; x++) {
			while ((ch = fgetc(f)) && ch == '\n')
				if (ch == EOF)
					goto end;
			GRAPH[y][x] = (char)ch;
			printf("%c", GRAPH[y][x]);
		}
		while ((ch = fgetc(f)) && ch != '\n')
			if (ch == EOF)
				goto end;
		printf("\n");
	}
	printf("\n");
end:
	fclose(f);
}

static int graph_predicate(const struct point *p)
{
	return (p->x >= 0 && p->x < GRAPH_X) &&
		(p->y >= 0 && p->y < GRAPH_Y);
}

static int grass_predicate(const struct point *p)
{
	return graph_predicate(p) && (GRAPH[p->y][p->x] == GRAPH_GRASS);
}

static int wall_predicate(const struct point *p)
{
	return graph_predicate(p) && (GRAPH[p->y][p->x] == GRAPH_WALL);
}

static int box_predicate(const struct point *p)
{
	return graph_predicate(p) && (GRAPH[p->y][p->x] == GRAPH_BOX);
}

static int bomb_predicate(const struct point *p)
{
	return graph_predicate(p) && (GRAPH[p->y][p->x] == GRAPH_BOMB);
}

static int playerb_predicate(const struct point *p)
{
	return graph_predicate(p) && (GRAPH[p->y][p->x] == GRAPH_PLAYER_B);
}

static int across_predicate(const struct point *p)
{
	return grass_predicate(p);
}

int print_node(struct list_head *node_head)
{
	int y, x;
	char PG[Y_MAX][X_MAX];	

	for (y = 0; y < GRAPH_Y; y++)
		for (x = 0; x < GRAPH_X; x++)
			PG[y][x] = '.';

	int nrnode = 0;
	struct node *node;
	list_for_each_entry(node, node_head, list) {
		nrnode++;
		PG[node->p.y][node->p.x] = '*';
	}

	for (y = 0; y < GRAPH_Y; y++) {
		for (x = 0; x < GRAPH_X; x++)
			printf("%c", PG[y][x]);
		printf("\n");
	}
	return nrnode;
}

int print_path(struct list_head *path_head)
{
	int nrpath = 0;
	struct path *path;
	list_for_each_entry(path, path_head, list) {
		nrpath++;
		int nrnode = print_node(&path->node);
		printf("steps: [%d]\n\n", nrnode);
	}
	return nrpath;
}

int main(int argc, char *argv[])
{
	load_graph(BFS_GRAPH);

	const struct point start = {.y=0, .x=0};

	int nr;
	struct list_head path_head;

	nr = bfs(&path_head, &start, across_predicate, box_predicate);
	printf("box path: %d\n", nr);
	print_path(&path_head);
	free_pathlist(&path_head);

	nr = bfs(&path_head, &start, across_predicate, wall_predicate);
	printf("wall path: %d\n", nr);
	print_path(&path_head);
	free_pathlist(&path_head);

	nr = bfs(&path_head, &start, across_predicate, bomb_predicate);
	printf("bomb path: %d\n", nr);
	print_path(&path_head);
	free_pathlist(&path_head);

	nr = bfs(&path_head, &start, across_predicate, playerb_predicate);
	printf("player B path: %d\n", nr);
	print_path(&path_head);
	free_pathlist(&path_head);

	return 0;
}
