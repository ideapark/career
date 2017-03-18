/*
 * sysstat/util/test/list_helper_test.c - list unit test
 *
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#include <stdlib.h>
#include <stdio.h>

#include "../list_helper.h"

struct kool_list {
	int to;
	struct list_head list;
	int from;
};

int main(int argc, char *argv[])
{
	int i;
	struct list_head *pos, *q;
	struct kool_list mylist, *tmp;

	INIT_LIST_HEAD(&mylist.list);

	printf("test for list_add()\n");
	for (i = 10; i > 0; --i) {
		tmp = (struct kool_list *)malloc(sizeof(struct kool_list));
		tmp->to = i + 10;
		tmp->from = i + 20;
		list_add_tail(&(tmp->list), &mylist.list);
		printf("[to=%d, from=%d]\n", tmp->to, tmp->from);
	}

	printf("test for list_for_each()\n");
	list_for_each(pos, &mylist.list) {
		tmp = list_entry(pos, struct kool_list, list);
		printf("[to=%d, from=%d]\n", tmp->to, tmp->from);
	}

	printf("test for list_for_each_entry()\n");
	list_for_each_entry(tmp, &mylist.list, list) {
		printf("[to=%d, from=%d]\n", tmp->to, tmp->from);
	}

	printf("test for list_for_each_safe()\n");
	list_for_each_safe(pos, q, &mylist.list) {
		tmp = list_entry(pos, struct kool_list, list);
		printf("free item [to=%d, from=%d]\n", tmp->to, tmp->from);
		list_del(pos);
		free(tmp);
	}

	return 0;
}
