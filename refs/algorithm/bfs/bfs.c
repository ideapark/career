/*
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#include "list.h"
#include "bfs.h"

#define LEN(arr) (sizeof(arr)/sizeof(arr[0]))

int bfs(struct list_head *path, const struct point *startp, Pass pfn, Target tfn)
{
	int nrpath = 0;

	INIT_LIST_HEAD(path);

	LIST_HEAD(openlist);
	LIST_HEAD(closelist);
	LIST_HEAD(backtrace);

	struct node *start_node = malloc_node();
	start_node->p = *startp;
	list_add(&start_node->list, &openlist);

	while (!list_empty(&openlist)) {

		struct node *front_node = list_entry(openlist.next, struct node, list);

		const struct point adjacent[] = {
			U(&front_node->p),
			D(&front_node->p),
			L(&front_node->p),
			R(&front_node->p)
		};

		for (unsigned i = 0; i < LEN(adjacent); i++) {

			/* backstrace */
			if (tfn && tfn(&adjacent[i])) {
				struct path *new_path = malloc_path();
				list_add(&new_path->link, path);

				struct node *n = malloc_node();
				n->p = adjacent[i];
				list_add(&n->list, &new_path->list);

				n = malloc_node();
				n->p = front_node->p;
				list_add(&n->list, &new_path->list);

				struct trace *trace;
				while (!EQ(&n->p, &start_node->p)) {
					list_for_each_entry(trace, &backtrace, link) {
						struct node *node;
						list_for_each_entry(node, &trace->list, list) {
							if (EQ(&node->p, &n->p)) {
								n = malloc_node();
								n->p = trace->p;
								list_add(&n->list, &new_path->list);
								break;
							}
						}
					}
				}

				nrpath++;
				continue;
			}

			if (pfn && !pfn(&adjacent[i]))
				continue;

			int exists = 0;

			struct node *open_node;
			list_for_each_entry(open_node, &openlist, list) {
				if (EQ(&open_node->p, &adjacent[i])) {
					exists = 1;
					break;
				}
			}
			if (exists)
				continue;

			struct node *close_node;
			list_for_each_entry(close_node, &closelist, list) {
				if (EQ(&close_node->p, &adjacent[i])) {
					exists = 1;
					break;
				}
			}
			if (exists)
				continue;

			struct node *backtrace_node = malloc_node();
			backtrace_node->p = adjacent[i];

			struct trace *exist_trace;
			list_for_each_entry(exist_trace, &backtrace, link) {
				if (EQ(&exist_trace->p, &front_node->p)) {
					list_add(&backtrace_node->list, &exist_trace->list);
					exists = 1;
					break;
				}
			}

			if (!exists) {
				struct trace *new_trace = malloc_trace();
				new_trace->p = front_node->p;
				list_add(&new_trace->link, &backtrace);
				list_add(&backtrace_node->list, &new_trace->list);
			}

			struct node *open_newnode = malloc_node();
			open_newnode->p = adjacent[i];
			list_add(&open_newnode->list, &openlist);
		}

		struct list_head *front_openhead = openlist.next;
		list_del(front_openhead);
		list_add(front_openhead, &closelist);
	}

	struct list_head *pos, *pos2, *n, *n2;
	list_for_each_safe(pos, n, &closelist) {
		list_del(pos);
		struct node *n = list_entry(pos, struct node, list);
		free(n);
	}
	list_for_each_safe(pos, n, &backtrace) {
		list_del(pos);
		struct trace *t = list_entry(pos, struct trace, link);
		list_for_each_safe(pos2, n2, &t->list) {
			list_del(pos2);
			struct node *n = list_entry(pos2, struct node, list);
			free(n);
		}
		free(t);
	}

	return nrpath;
}
