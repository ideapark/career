/*
The authors of this work have released all rights to it and placed it in the
public domain under the Creative Commons CC0 1.0 waiver
(http://creativecommons.org/publicdomain/zero/1.0/).

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Retrieved from: http://en.literateprograms.org/Red-black_tree_(C)?oldid=19567
*/

#include <assert.h>
#include <stdlib.h>

#include "rbtree.h"

typedef rbtree_node node;
typedef enum rbtree_node_color color;

static node grandparent(node n);
static node sibling(node n);
static node uncle(node n);
static void verify_properties(rbtree t);
static void verify_property_1(node root);
static void verify_property_2(node root);
static color node_color(node n);
static void verify_property_4(node root);
static void verify_property_5(node root);
static void verify_property_5_helper(node n, int black_count, int *black_count_path);

static node new_node(void *key, void *value, color node_color, node left, node right);
static node lookup_node(rbtree t, void *key, compare_func compare);
static void rotate_left(rbtree t, node n);
static void rotate_right(rbtree t, node n);

static void replace_node(rbtree t, node oldn, node newn);
static void insert_case1(rbtree t, node n);
static void insert_case2(rbtree t, node n);
static void insert_case3(rbtree t, node n);
static void insert_case4(rbtree t, node n);
static void insert_case5(rbtree t, node n);
static node maximum_node(node root);
static void delete_case1(rbtree t, node n);
static void delete_case2(rbtree t, node n);
static void delete_case3(rbtree t, node n);
static void delete_case4(rbtree t, node n);
static void delete_case5(rbtree t, node n);
static void delete_case6(rbtree t, node n);

/*
The grandparent of a node, its parent's parent. We use assertions to make sure
the we don't attempt to access the grandparent of a node that doesn't have one,
such as the root node or its children:
 */
node grandparent(node n)
{
	assert(n != NULL);
	assert(n->parent != NULL);	/* Not the root node */
	assert(n->parent->parent != NULL);	/* Not child of root */
	return n->parent->parent;
}

/*
The sibling of a node, defined as the other child of its parent. Note that the
sibling may be NULL, if the parent has only one child.
 */
node sibling(node n)
{
	assert(n != NULL);
	assert(n->parent != NULL);	/* Root node has no sibling */
	if (n == n->parent->left)
		return n->parent->right;
	else
		return n->parent->left;
}

/*
The uncle of a node, defined as the sibling of its parent. The uncle may also be
NULL, if the grandparent has only one child.
 */
node uncle(node n)
{
	assert(n != NULL);
	assert(n->parent != NULL);	/* Root node has no uncle */
	assert(n->parent->parent != NULL);	/* Children of root have no uncle */
	return sibling(n->parent);
}

/*
We will at all times enforce the following five properties, which provide a
theoretical guarantee that the tree remains blanced. We will have a helper
function verify_properties() that asserts all five properties in a debug build,
to help verify the correctness of our implementation and formally demonstrate
their meaning. Note that many of these tests walk the tree, making them very
expensive - for this reason we require the symbol VERIFY_RBTREE to be defined to
turn them on.
 */
void verify_properties(rbtree t)
{
#ifdef VERIFY_RBTREE
	verify_property_1(t->root);
	verify_property_2(t->root);
	/* Property 3 is implicit */
	verify_property_4(t->root);
	verify_property_5(t->root);
#endif
}

/*
Each node is either red or black.
 */
void verify_property_1(node n)
{
	assert(node_color(n) == RED || node_color(n) == BLACK);
	if (n == NULL)
		return;
	verify_property_1(n->left);
	verify_property_1(n->right);
}

/*
The root node is black.
 */
void verify_property_2(node root)
{
	assert(node_color(root) == BLACK);
}

/*
All leaves are black and contain no data. Since we represent these empty leaves
using NULL, this property is implicitly assured by always treating NULL as
black. To this end we create a node_color() helper function.
 */
color node_color(node n)
{
	return n == NULL ? BLACK : n->color;
}

/*
Every red node has two children, and both are black (or equivalently, the parent
of every red node is black).
 */
void verify_property_4(node n)
{
	if (node_color(n) == RED) {
		assert(node_color(n->left) == BLACK);
		assert(node_color(n->right) == BLACK);
		assert(node_color(n->parent) == BLACK);
	}
	if (n == NULL)
		return;
	verify_property_4(n->left);
	verify_property_4(n->right);
}

/*
All paths from any given node to its leaf nodes contain the same number of black
nodes. This one is the strickiest to verify; we do it by traversing the tree,
incrementing a black node count as we go. The first time we reach a leaf we save
the count. When we subsequently reach other leaves, we compare the count to this
saved count.
 */
void verify_property_5(node root)
{
	int black_count_path = -1;
	verify_property_5_helper(root, 0, &black_count_path);
}

void verify_property_5_helper(node n, int black_count, int *path_black_count)
{
	if (node_color(n) == BLACK) {
		black_count++;
	}
	if (n == NULL) {
		if (*path_black_count == -1) {
			*path_black_count = black_count;
		} else {
			assert(black_count == *path_black_count);
		}
		return;
	}
	verify_property_5_helper(n->left, black_count, path_black_count);
	verify_property_5_helper(n->right, black_count, path_black_count);
}

/*
Properties 4 and 5 together guarantee that no path in the tree is more than
about twice as long as any other path, which guarantees that it has O(log n)
height.
 */

/*
An empty tree is represented by a tree with a NULL root. This object provides a
starting point for other operations.
 */
rbtree rbtree_create()
{
	rbtree t = malloc(sizeof(struct rbtree_t));
	t->root = NULL;
	verify_properties(t);
	return t;
}

/*
We have a helper function to allocate and initialize a new node.
 */
node new_node(void *key, void *value, color node_color, node left, node right)
{
	node result = malloc(sizeof(struct rbtree_node_t));
	result->key = key;
	result->value = value;
	result->color = node_color;
	result->left = left;
	result->right = right;
	if (left != NULL)
		left->parent = result;
	if (right != NULL)
		right->parent = result;
	result->parent = NULL;
	return result;
}

/*
Read-only operations on a red-black tree, such as searching for a key and
getting the corresponding value, require no modification from those used for
binary search trees, because every red-black tree is a specialization of a
simple binary search tree.

We begin by creating a helper function that gets a pointer to the node with a
given key. If the key is not found, it returns NULL. This will be useful later
for deletion.

The client must pass in a comparison function to compare the data values, which
have unknown type. Like the comparison function passed to the library function
qsort(), it returns a negative value, zero, or positive value, depending if the
left value is less than, equal to, or greater than the right value,
respectively.
 */
node lookup_node(rbtree t, void *key, compare_func compare)
{
	node n = t->root;
	while (n != NULL) {
		int comp_result = compare(key, n->key);
		if (comp_result == 0) {
			return n;
		} else if (comp_result < 0) {
			n = n->left;
		} else {
			assert(comp_result > 0);
			n = n->right;
		}
	}
	return n;
}

/*
Now looking up a value is straightforward, by finding the node and extracting
the data if lookup succeeded. We return NULL if the key was not found (implying
that NULL cannot be used as a value unless all lookups are expected to succeed).
 */
void *rbtree_lookup(rbtree t, void *key, compare_func compare)
{
	node n = lookup_node(t, key, compare);
	return n == NULL ? NULL : n->value;
}

/*
Both insertion and deletion rely on a fundamental operation for reducing tree
height called a rotation. A rotation locally changes the structure of the tree
without changing the in-order order of the sequence of values that it stores.

We create two helper functions, one to perform a left rotation and one to
perform a right rotation; each takes the highest node in the subtree as an
argument.
 */

void rotate_left(rbtree t, node n)
{
	node r = n->right;
	replace_node(t, n, r);
	n->right = r->left;
	if (r->left != NULL) {
		r->left->parent = n;
	}
	r->left = n;
	n->parent = r;
}

void rotate_right(rbtree t, node n)
{
	node L = n->left;
	replace_node(t, n, L);
	n->left = L->right;
	if (L->right != NULL) {
		L->right->parent = n;
	}
	L->right = n;
	n->parent = L;
}

/*
Here, replace_node() is a helper function that cuts a node away from its parent,
substituting a new node (or NULL) in its place. It simplifies consistent
updating of parent and child pointers. It needs the tree passed in because it
may change which node is the root.
 */
void replace_node(rbtree t, node oldn, node newn)
{
	if (oldn->parent == NULL) {
		t->root = newn;
	} else {
		if (oldn == oldn->parent->left)
			oldn->parent->left = newn;
		else
			oldn->parent->right = newn;
	}
	if (newn != NULL) {
		newn->parent = oldn->parent;
	}
}

/*
When inserting a new value, we first insert it into the tree as we would into an
ordinary binary search tree. If the key already exists, we just replace the
value (since we're implementing an associative array). Otherwise, we find the
place in the tree where the new pair belongs, then attach a newly created red
node containing the value.
 */
void rbtree_insert(rbtree t, void *key, void *value, compare_func compare)
{
	node inserted_node = new_node(key, value, RED, NULL, NULL);
	if (t->root == NULL) {
		t->root = inserted_node;
	} else {
		node n = t->root;
		while (1) {
			int comp_result = compare(key, n->key);
			if (comp_result == 0) {
				n->value = value;
				return;
			} else if (comp_result < 0) {
				if (n->left == NULL) {
					n->left = inserted_node;
					break;
				} else {
					n = n->left;
				}
			} else {
				assert(comp_result > 0);
				if (n->right == NULL) {
					n->right = inserted_node;
					break;
				} else {
					n = n->right;
				}
			}
		}
		inserted_node->parent = n;
	}
	insert_case1(t, inserted_node);
	verify_properties(t);
}

/*
The problem is that the resulting tree may not satify our five red-black tree
properties. The call to insert_case1() above begins the process of correcting
the tree so that it satifies the properties once more.
 */

/*
In this case, the new node is now the root node of the tree. Since the root node
must be black, and changing its color adds the same number of black nodes to
every path, we simply recolor it black. Because only the root node has no
parent, we can assume henceforth that the node has a parent.
 */
void insert_case1(rbtree t, node n)
{
	if (n->parent == NULL)
		n->color = BLACK;
	else
		insert_case2(t, n);
}

/*
In this case, the new node has a black parent. All the properties are still
satisfied and we return.
 */
void insert_case2(rbtree t, node n)
{
	if (node_color(n->parent) == BLACK)
		return;		/* Tree is still valid */
	else
		insert_case3(t, n);
}

/*
In this case, the uncle node is red. We recolor the parent and uncle black and
the grandparent red. However, the red grandparent node may now violate the
red-black tree properties; we recursively invoke this procedure on it from case
1 to deal with this.
 */
void insert_case3(rbtree t, node n)
{
	if (node_color(uncle(n)) == RED) {
		n->parent->color = BLACK;
		uncle(n)->color = BLACK;
		grandparent(n)->color = RED;
		insert_case1(t, grandparent(n));
	} else {
		insert_case4(t, n);
	}
}

/*
In this case, we deal with two cases that are mirror images of one another:

  1. The new node is the right child of its parent and the parent is the left
     child of the grandparent. In this case we rotate left about the parent.

  2. The new node is the left child of its parent and the parent is the right
     child of the grandparent. In this case we rotate right about the parent.

Neither of these fixes the properties, but they put the tree in the correct form
to apply case 5.
 */
void insert_case4(rbtree t, node n)
{
	if (n == n->parent->right && n->parent == grandparent(n)->left) {
		rotate_left(t, n->parent);
		n = n->left;
	} else if (n == n->parent->left && n->parent == grandparent(n)->right) {
		rotate_right(t, n->parent);
		n = n->right;
	}
	insert_case5(t, n);
}

/*
In this final case, we deal with two cases that are mirror images of one
another:

  1. The new node is the left child of its parent and the parent is the left
     child of the grandparent. In this case we rotate right about the
     grandparent.

  2. The new node is the right child of its parent and the parent is the right
     child of the grandparent. In this case we rotate left about the
     grandparent.

Now the properties are satisfied and all cases have been covered.
 */
void insert_case5(rbtree t, node n)
{
	n->parent->color = BLACK;
	grandparent(n)->color = RED;
	if (n == n->parent->left && n->parent == grandparent(n)->left) {
		rotate_right(t, grandparent(n));
	} else {
		assert(n == n->parent->right
		       && n->parent == grandparent(n)->right);
		rotate_left(t, grandparent(n));
	}
}

/*
We begin by finding the node to be deleted with lookup_node() and deleting it
precisely as we would in a binary search tree. There are two cases for removal,
depending on whether the node to be deleted has at most one, or two non-leaf
children. A node with at most on non-leaf child can simply be replaced with its
non-leaf child. When deleting a node with two non-leaf chidlren, we copy the
value from the in-order predecessor (the maximum or rightmost element in the
left subtree) into the node to be deleted, and then we delete the predeessor
node, which has only one non-leaf child. This same procedure also works in a
red-black tree without affecting any properties.
 */
void rbtree_delete(rbtree t, void *key, compare_func compare)
{
	node child;
	node n = lookup_node(t, key, compare);
	if (n == NULL)
		return;		/* Key not found, do nothing */
	if (n->left != NULL && n->right != NULL) {
		/* Copy key/value from predecessor and then delete it instead */
		node pred = maximum_node(n->left);
		n->key = pred->key;
		n->value = pred->value;
		n = pred;
	}

	assert(n->left == NULL || n->right == NULL);
	child = n->right == NULL ? n->left : n->right;
	if (node_color(n) == BLACK) {
		n->color = node_color(child);
		delete_case1(t, n);
	}
	replace_node(t, n, child);
	if (n->parent == NULL && child != NULL)	// root should be black
		child->color = BLACK;
	free(n);

	verify_properties(t);
}

/*
The maximum_node() helper function just walks right until it reaches the last
non-leaf.
 */
static node maximum_node(node n)
{
	assert(n != NULL);
	while (n->right != NULL) {
		n = n->right;
	}
	return n;
}

/*
However, before deleting the node, we must ensure that doing so does not violate
the red-black tree properties. If the node we delete is black, and we cannot
change its child from red to black to compensate, then we would have one less
black node on every path through the child node. We must adjust the tree around
the node being deleted to compensate.
 */

/*
In this case, N has become the root node. The deletion removed one black node
from every path, so no properties are violated.
 */
void delete_case1(rbtree t, node n)
{
	if (n->parent == NULL)
		return;
	else
		delete_case2(t, n);
}

/*
N has a red sibling. In this case we exchange the colors of the parent and
sibling, then rotate about the parent so that the sibling becomes the parent of
its former parent. This does not restore the tree properties, but reduces the
problem to one of the remaining cases.
 */
void delete_case2(rbtree t, node n)
{
	if (node_color(sibling(n)) == RED) {
		n->parent->color = RED;
		sibling(n)->color = BLACK;
		if (n == n->parent->left)
			rotate_left(t, n->parent);
		else
			rotate_right(t, n->parent);
	}
	delete_case3(t, n);
}

/*
In this case N's parent, sibling, and sibling's children are black. In this case
we paint the sibling red. Now all paths passing through N's parent have one less
black node than before the deletion, so we must recursively run this procedure
from case 1 on N's parent.
 */
void delete_case3(rbtree t, node n)
{
	if (node_color(n->parent) == BLACK &&
	    node_color(sibling(n)) == BLACK &&
	    node_color(sibling(n)->left) == BLACK &&
	    node_color(sibling(n)->right) == BLACK) {
		sibling(n)->color = RED;
		delete_case1(t, n->parent);
	} else {
		delete_case4(t, n);
	}
}

/*
N's sibling and sibling's children are black, but its parent is red. We exchange
the colors of the sibling and parent; this restore the tree properties.
 */
void delete_case4(rbtree t, node n)
{
	if (node_color(n->parent) == RED &&
	    node_color(sibling(n)) == BLACK &&
	    node_color(sibling(n)->left) == BLACK &&
	    node_color(sibling(n)->right) == BLACK) {
		sibling(n)->color = RED;
		n->parent->color = BLACK;
	} else {
		delete_case5(t, n);
	}
}

/*
There are two cases handled here which are mirror images of one another:

  1. N's sibling S is black, S's left child is red, S's right child is black,
     and N is the left child of its parent. We exchange the colors of S and its
     left sibling and rotate right at S.

  2. N's sibling S is black, S's right child is red, S's left child is black,
     and N is the right child of its parent. We exchange the colors of S and its
     right sibling and rotate left at S.
 */
void delete_case5(rbtree t, node n)
{
	if (n == n->parent->left &&
	    node_color(sibling(n)) == BLACK &&
	    node_color(sibling(n)->left) == RED &&
	    node_color(sibling(n)->right) == BLACK) {
		sibling(n)->color = RED;
		sibling(n)->left->color = BLACK;
		rotate_right(t, sibling(n));
	} else if (n == n->parent->right &&
		   node_color(sibling(n)) == BLACK &&
		   node_color(sibling(n)->right) == RED &&
		   node_color(sibling(n)->left) == BLACK) {
		sibling(n)->color = RED;
		sibling(n)->right->color = BLACK;
		rotate_left(t, sibling(n));
	}
	delete_case6(t, n);
}

/*
There are two cases handled here which are mirror images of one another:

  1. N's sibling S is black, S's right child is red, and N is the left child of
     its parent. We exchange the colors of N's parent and sibling, make S's
     right child black, then rotate left at N's parent.

  2. N's sibling S is black, S's left child is red, and N is the right child of
     its parent. We exchange the colors of N's parent and sibling, make S's left
     child black, then rotate right at N's parent.

This accomplishes three things at once:

  1. We add a black node to all paths through N, either by adding a black S to
     those paths or by recoloring N's parent black.

  2. We remove a black node from all paths through S's red child, either by
     removing P from those paths or by recoloring S.

  3. We recolor S's red child black, adding a black node back to all paths
     through S's red child.

S's left child has become a child of N's parent during the rotation and so is
unaffected.

Again, the function calls all use tail recursion, so the algorithm is in-place.
Additionally, no recursive calls will be made after a rotation, so no more than
three rotations are made.
 */
void delete_case6(rbtree t, node n)
{
	sibling(n)->color = node_color(n->parent);
	n->parent->color = BLACK;
	if (n == n->parent->left) {
		assert(node_color(sibling(n)->right) == RED);
		sibling(n)->right->color = BLACK;
		rotate_left(t, n->parent);
	} else {
		assert(node_color(sibling(n)->left) == RED);
		sibling(n)->left->color = BLACK;
		rotate_right(t, n->parent);
	}
}
