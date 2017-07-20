/*
 * Copyright (c) Zhou Peng <p@ctriple.cn>
 *
 * Breadth first search algorithm implemented by C programming language.
 */

#include "list.h"
#include "bfs.h"

#define LEN(arr) (sizeof(arr)/sizeof(arr[0]))

int bfs_path(struct list_head *pathlist, const struct point *startp,
	     Pass pfn, Target tfn)
{
	int nrpath = 0;

	INIT_LIST_HEAD(pathlist);

	LIST_HEAD(openlist);
	LIST_HEAD(closelist);
	LIST_HEAD(backtrace);

	struct node *start_node = malloc_node();
	start_node->p = *startp;
	list_add_tail(&start_node->list, &openlist);

	while (!list_empty(&openlist)) {

		struct node *front_node = list_entry(openlist.next, struct node, list);

		const struct point adjs[] = {
			U(&front_node->p),
			D(&front_node->p),
			L(&front_node->p),
			R(&front_node->p)
		};

		unsigned i;
		for (i = 0; i < LEN(adjs); i++) {

			/* backstrace path */
			if (tfn && tfn(&adjs[i])) {
				struct path *new_path = malloc_path();
				list_add_tail(&new_path->list, pathlist);

				struct node *back_node;

				back_node = malloc_node();
				back_node->p = adjs[i];
				list_add(&back_node->list, &new_path->node);

				back_node = malloc_node();
				back_node->p = front_node->p;
				list_add(&back_node->list, &new_path->node);

				while (!EQ(&back_node->p, &start_node->p)) {
					struct trace *trace;
					list_for_each_entry(trace, &backtrace, list) {
						struct node *node;
						list_for_each_entry(node, &trace->node, list) {
							if (EQ(&node->p, &back_node->p)) {
								back_node = malloc_node();
								back_node->p = trace->p;
								list_add(&back_node->list, &new_path->node);
								break;
							}
						}
					}
				}

				nrpath++;
				continue;
			}

			if (pfn && !pfn(&adjs[i]))
				continue;

			/* expand by breadth */
			int exists = 0;

			struct node *open_node;
			list_for_each_entry(open_node, &openlist, list) {
				if (EQ(&open_node->p, &adjs[i])) {
					exists = 1;
					break;
				}
			}
			if (exists)
				continue;

			struct node *close_node;
			list_for_each_entry(close_node, &closelist, list) {
				if (EQ(&close_node->p, &adjs[i])) {
					exists = 1;
					break;
				}
			}
			if (exists)
				continue;

			struct node *open_newnode = malloc_node();
			open_newnode->p = adjs[i];
			list_add_tail(&open_newnode->list, &openlist);

			/* save backtrace */
			struct node *backtrace_node = malloc_node();
			backtrace_node->p = adjs[i];

			struct trace *exist_trace;
			list_for_each_entry(exist_trace, &backtrace, list) {
				if (EQ(&exist_trace->p, &front_node->p)) {
					list_add(&backtrace_node->list, &exist_trace->node);
					exists = 1;
					break;
				}
			}

			if (!exists) {
				struct trace *new_trace = malloc_trace();
				new_trace->p = front_node->p;
				list_add(&new_trace->list, &backtrace);
				list_add(&backtrace_node->list, &new_trace->node);
			}
		}

		struct list_head *front_head = openlist.next;
		list_del(front_head);
		list_add(front_head, &closelist);
	}

	free_nodelist(&closelist);
	free_tracelist(&backtrace);

	return nrpath;
}
