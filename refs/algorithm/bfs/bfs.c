/*
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#include <stdlib.h>

#include "list.h"
#include "bfs.h"

#define LEN(arr) (sizeof(arr)/sizeof(arr[0]))

int bfs(struct list_head *path, const struct point *start, Pass pfn, Target tfn)
{
	int found = 0;	
	
	LIST_HEAD(open_list);
	LIST_HEAD(close_list);
	LIST_HEAD(target_found);

	INIT_LIST_HEAD(path);

	struct node *start_node = malloc(sizeof(struct node));
	INIT_LIST_HEAD(&start_node->list);
	start_node->p = *start;
	list_add(&start_node->list, &open_list);

	while (!list_empty(&open_list)) {
		struct node *node = list_entry(open_list.next, struct node, list);

		const struct point neighbors[] = {
			UP(&node->p),
			DOWN(&node->p),
			LEFT(&node->p),
			RIGHT(&node->p)
		};

		for (unsigned i = 0; i < LEN(neighbors); /*NULL*/) {
			/* backstrace */
			if (tfn && tfn(&neighbors[i])) {
				found++;
				goto next;
			}
			if (pfn && !pfn(&neighbors[i]))
				goto next;

			struct node *pos;
			/* visiting */
			list_for_each_entry(pos, &open_list, list) {
				if (neighbors[i].y == pos->p.y && neighbors[i].x == pos->p.x)
					goto next;
			}
			/* visited */
			list_for_each_entry(pos, &close_list, list) {
				if (neighbors[i].y == pos->p.y && neighbors[i].x == pos->p.x)
					goto next;
			}

			struct node *new = malloc(sizeof(struct node));
			INIT_LIST_HEAD(&new->list);
			new->p = neighbors[i];
			list_add(&new->list, &open_list);
		next:
			i++;
		}

		struct list_head *tmp = open_list.next;
		list_del(tmp);
		list_add(tmp, &close_list);
	}

	/* clean */
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
