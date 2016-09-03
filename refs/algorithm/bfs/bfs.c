/*
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#include "list.h"
#include "bfs.h"

#define LEN(arr) (sizeof(arr)/sizeof(arr[0]))

int bfs(struct list_head *path, const struct point *startp, Pass pfn, Target tfn)
{
	int nrpath = 0;

	LIST_HEAD(openlist);
	LIST_HEAD(closelist);
	LIST_HEAD(backtrace);

	INIT_LIST_HEAD(path);

	struct node *start = new_node();
	start->p = *startp;

	list_add(&start->list, &openlist);

	while (!list_empty(&openlist)) {

		struct node *node = list_entry(openlist.next, struct node, list);

		const struct point neighbors[] = {
			U(&node->p), D(&node->p),
			L(&node->p), R(&node->p)
		};

		for (unsigned i = 0; i < LEN(neighbors); i++) {
			int found = 0;

			/* backstrace */
			if (tfn && tfn(&neighbors[i])) {
				struct path *path = new_path();
				list_add(&path->link, path);

				nrpath++;
				continue;
			}

			if (pfn && !pfn(&neighbors[i]))
				continue;

			struct node *pos;
			list_for_each_entry(pos, &openlist, list) {
				if (EQ(&pos->p, &neighbors[i])) {
					found = 1;
					break;
				}
			}
			if (found)
				continue;

			list_for_each_entry(pos, &closelist, list) {
				if (EQ(&pos->p, &neighbors[i])) {
					found = 1;
					break;
				}
			}
			if (found)
				continue;

			/* backtrace clue */
			struct node *btnode = new_node();
			btnode->p = neighbors[i];

			struct trace *trace;
			list_for_each_entry(trace, &backtrace, link) {
				if (EQ(&node->p, &trace->p)) {
					found = 1;
					list_add(&btnode->list, &trace->list);
					break;
				}
			}

			/* new trace */
			if (!found) {
				trace = new_trace();
				trace->p = node->p;
				list_add(&trace->link, &backtrace);
				list_add(&btnode->list, &trace->list);
			}

			struct node *new = new_node();
			new->p = neighbors[i];
			list_add(&new->list, &openlist);
		}

		struct list_head *tmp = openlist.next;
		list_del(tmp);
		list_add(tmp, &closelist);
	}

	/* clean env */
	struct list_head *pos, *pos2, *n, *n2;
	list_for_each_safe(pos, n, &closelist) {
		list_del(pos);
		struct node *node = list_entry(pos, struct node, list);
		free(node);
	}
	list_for_each_safe(pos, n, &backtrace) {
		list_del(pos);
		struct trace *trace = list_entry(pos, struct trace, link);
		list_for_each_safe(pos2, n2, &trace->list) {
			list_del(pos2);
			struct node *node = list_entry(pos2, struct node, list);
			free(node);
		}
		free(trace);
	}

	return nrpath;
}
