/*
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#include <stdlib.h>

#include "list.h"
#include "bfs.h"

#define LEN(arr) (sizeof(arr)/sizeof(arr[0]))

int bfs(struct list_head *path, const struct point *startp, Pass pfn, Target tfn)
{
	int found = 0;

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

		for (unsigned i = 0; i < LEN(neighbors); /*NULL*/) {

			/* backstrace */
			if (tfn && tfn(&neighbors[i])) {
				struct path *path = new_path();
				list_add(&path->link, path);

				found++;
				goto next;
			}

			if (pfn && !pfn(&neighbors[i]))
				goto next;

			struct node *pos;
			list_for_each_entry(pos, &openlist, list) {
				if (EQ(&pos->p, &neighbors[i]))
					goto next;
			}
			list_for_each_entry(pos, &closelist, list) {
				if (EQ(&pos->p, &neighbors[i]))
					goto next;
			}
			/* remember clue */
			struct node *btnode = new_node();
			btnode->p = neighbors[i];

			struct trace *trace;
			list_for_each_entry(trace, &backtrace, link) {
				if (EQ(&node->p, &trace->p)) {
					list_add(&btnode->list, &trace->list);
					goto open;
				}
			}

			/* new trace */
			trace = new_trace();
			trace->p = node->p;
			list_add(&trace->link, &backtrace);
			list_add(&node->list, &trace->list);
open:
			struct node *new = new_node();
			new->p = neighbors[i];
			list_add(&new->list, &openlist);
next:
			i++;
		}

		struct list_head *tmp = openlist.next;
		list_del(tmp);
		list_add(tmp, &closelist);
	}

	/* clean */
	struct list_head *pos, *n;
	list_for_each_safe(pos, n, &openlist) {
		list_del(pos);
		struct node *node = list_entry(pos, struct node, list);
		free(node);
	}
	list_for_each_safe(pos, n, &closelist) {
		list_del(pos);
		struct node *node = list_entry(pos, struct node, list);
		free(node);
	}

	return found;
}
