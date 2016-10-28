/*
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#ifndef REPORTER_AVLTREE_H
#define REPORTER_AVLTREE_H

#include <inttypes.h>
#include <list>
#include <iostream>

#include "reporter_bfdsupport.h"

namespace reporter {

class avl_tree
{
public:
	avl_tree();

public:
	vma_node *leftmost(vma_node *root);
	vma_node *rightmost(vma_node *root);

public:
	vma_node *find(vma_node *root, uint32_t vma);
	vma_node *insert(vma_node *&root, vma_node *node);
	vma_node *rmnode(vma_node *&root);
	void flat(const vma_node *root,
		  std::list<const vma_node *> &flat_tree) const;
	void debug_print(const vma_node *root) const;

private:
	int height(vma_node *root);
	int diff(vma_node *root);
	vma_node *rr_rotation(vma_node *parent);
	vma_node *ll_rotation(vma_node *parent);
	vma_node *lr_rotation(vma_node *parent);
	vma_node *rl_rotation(vma_node *parent);
	vma_node *balance(vma_node *root);

public:
	vma_node *root_node;
};

} /* namespace reporter */

#endif /* REPORTER_AVLTREE_H */
