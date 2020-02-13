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

/*
A red-black tree is a type of self-balancing binary search tree typically used
to implement associative arrays. It has O(log n) worst-case time for each
operation and is quite efficient in practice.
 */

#ifndef _RBTREE_H_
#define _RBTREE_H_

/*
A red-black tree is a type of binary search tree, so each node in the tree has a
parent (except the root node) and at most two children. The tree as a whole will
be identified by its root node. For ease of implementation, we will have each
node retain a pointer to both its children as well as its parent node (NULL for
the root). Keeping parent nodes costs space and is not strictly necessary, but
makes it easy to follow the tree in any direction without maintaining an
auxilary stack. Our red-black tree will implement an associative array, so we
will store both the key and its associated value in a void*.
 */
enum rbtree_node_color { RED, BLACK };

typedef struct rbtree_node_t {
	void *key;
	void *value;
	struct rbtree_node_t *left;
	struct rbtree_node_t *right;
	struct rbtree_node_t *parent;
	enum rbtree_node_color color;
} *rbtree_node;

typedef struct rbtree_t {
	rbtree_node root;
} *rbtree;

typedef int (*compare_func)(void *left, void *right);

rbtree rbtree_create();
void *rbtree_lookup(rbtree t, void *key, compare_func compare);
void rbtree_insert(rbtree t, void *key, void *value, compare_func compare);
void rbtree_delete(rbtree t, void *key, compare_func compare);

#endif
