/*
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#include <stdlib.h>

#include "list.h"
#include "bfs.h"

#define LEN(arr) (sizeof(arr)/sizeof(arr[0]))

int bfs(struct list_head *path, const struct point *start, Pass Pfn, Target Tfn)
{
	int found = 0;	
	
	LIST_HEAD(open_list);
	LIST_HEAD(close_list);
	LIST_HEAD(target_found);

	INIT_LIST_HEAD(path);

	struct node *start_node = malloc(sizeof(struct node));
	start_node->p = *start;
	INIT_LIST_HEAD(&start_node->list);

	list_add_tail(&start_node->list, &open_list);

	while (!list_empty(&open_list)) {
		struct node *node = list_entry(open_list.next, struct node, list);
		struct point front = node->p;

		/* backtrace path */
		if (Tfn && Tfn(&front)) {
			found++;
		}

		const struct point neighbors[] = {
			UP(&front),
			DOWN(&front),
			LEFT(&front),
			RIGHT(&front)
		};

		/* breadth first */
		for (unsigned i = 0; i < LEN(neighbors); /*NULL*/) {
			if (Pfn && !Pfn(&neighbors[i]) && Tfn && !Tfn(&neighbors[i]))
				goto next;

			struct node *pos;
			list_for_each_entry(pos, &open_list, list) {
				if (neighbors[i].y == pos->p.y && neighbors[i].x == pos->p.x)
					goto next;
			}
			list_for_each_entry(pos, &close_list, list) {
				if (neighbors[i].y == pos->p.y && neighbors[i].x == pos->p.x)
					goto next;
			}

			struct node *new_node = malloc(sizeof(struct node));
			new_node->p = neighbors[i];
			INIT_LIST_HEAD(&new_node->list);
			list_add_tail(&new_node->list, &open_list);
		next:
			i++;
		}

		list_add_tail(open_list.next, &close_list);
		list_del(open_list.next);
	}

	/* free list */
	struct list_head *pos, *n;
	list_for_each_safe(pos, n, &open_list) {
		list_del(pos);
		struct node *node = list_entry(pos, struct node, list);
		free(node);
	}
	list_for_each_safe(pos, n, &close_list) {
		list_del(pos);
		struct node *node = list_entry(pos, struct node, list);
		free(node);
	}
	
	return found;
}
