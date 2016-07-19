/*
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#include <algorithm>
#include "reporter_avltree.h"

namespace reporter {

static int cmp_node(const vma_node *left, const vma_node *right)
{
  if (left->vma_end <= right->vma_begin)
    return -1;
  else if (left->vma_begin >= right->vma_end)
    return 1;
  else
    return 0;
}

static void print_node(const vma_node *node)
{
  std::cout << "[" << node->vma_begin << ", " << node->vma_end << "] -> "
            << node->unix_path << " (" << node->bfd_key << ")" << std::endl;
}

avl_tree::avl_tree()
{
  root_node = 0;
}

int avl_tree::height(vma_node *root)
{
  int h = 0;

  if (root != 0) {
    int l_height = height(root->left);
    int r_height = height(root->right);
    int max_height = std::max(l_height, r_height);
    h = max_height + 1;
  }
  return h;
}

int avl_tree::diff(vma_node *root)
{
  int l_height = height(root->left);
  int r_height = height(root->right);
  int b_factor = l_height - r_height;
  return b_factor;
}

vma_node *avl_tree::rr_rotation(vma_node *parent)
{
  vma_node *temp;

  temp = parent->right;
  parent->right = temp->left;
  temp->left = parent;
  return temp;
}

vma_node *avl_tree::ll_rotation(vma_node *parent)
{
  vma_node *temp;

  temp = parent->left;
  parent->left = temp->right;
  temp->right = parent;
  return temp;
}

vma_node *avl_tree::lr_rotation(vma_node *parent)
{
  vma_node *temp;

  temp = parent->left;
  parent->left = rr_rotation(temp);
  return ll_rotation(parent);
}

vma_node *avl_tree::rl_rotation(vma_node *parent)
{
  vma_node *temp;

  temp = parent->right;
  parent->right = ll_rotation(temp);
  return rr_rotation(parent);
}

vma_node *avl_tree::balance(vma_node *root)
{
  int b_factor = diff(root);

  if (b_factor > 1) {
    if (diff(root->left) > 0)
      root = ll_rotation(root);
    else
      root = lr_rotation(root);
  } else if (b_factor < -1) {
    if (diff(root->right) > 0)
      root = rl_rotation(root);
    else
      root = rr_rotation(root);
  }
  return root;
}

vma_node *avl_tree::find(vma_node *root, uint32_t vma)
{
  if (root == 0)
    return 0;

  if (root->vma_begin > vma)
    return find(root->left, vma);
  else if (root->vma_end < vma)
    return find(root->right, vma);
  else
    return root;
}

vma_node *avl_tree::insert(vma_node *&root, vma_node *node)
{
  if (root == 0) {
    root = node;
    return root;
  }

  if (cmp_node(root, node) < 0) {
    root->right = insert(root->right, node);
    root = balance(root);
  } else if (cmp_node(root, node) > 0) {
    root->left = insert(root->left, node);
    root = balance(root);
  } else {
    return root;
  }

  return root;
}

vma_node *avl_tree::rmnode(vma_node *&root)
{
  vma_node *temp = root;

  if (temp == 0)
    return 0;

  if (root->left != 0)
    return rmnode(root->left);
  else if (root->right != 0)
    return rmnode(root->right);
  else {
    root = 0;
    return temp;
  }
}

vma_node *avl_tree::leftmost(vma_node *root)
{
  if (root != 0 && root->left != 0)
    return leftmost(root->left);
  else
    return root;
}

vma_node *avl_tree::rightmost(vma_node *root)
{
  if (root != 0 && root->right != 0)
    return rightmost(root->right);
  else
    return root;
}

void avl_tree::flat(const vma_node *root,
                    std::list<const vma_node *> &flat_tree) const
{
  if (root == 0)
    return;

  flat(root->left, flat_tree);
  flat_tree.push_back(root);
  flat(root->right, flat_tree);
}

void avl_tree::debug_print(const vma_node *root) const
{
  if (root == 0)
    return;

  debug_print(root->left);
  print_node(root);
  debug_print(root->right);
}

} /* namespace reporter */
