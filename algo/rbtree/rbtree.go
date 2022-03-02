// Copyright 2020 © Park Zhou <park@ideapark.io>

// Package rbtree provides a red-black tree algorithm implemention
//
// A red-black tree is a type of self-balancing binary search tree typically
// used to implement associative arrays. It has O(log n) worst-case time for
// each operation and is quite efficient in practice.
//
// https://en.wikipedia.org/wiki/Red-Black_tree
//
package rbtree

// Interface describes a red-black tree interface that an implemention must be
// satisfied.
type Interface interface {
	Lookup(key interface{}) (val interface{}, ok bool)
	Insert(key interface{}, val interface{})
	Delete(key interface{})
}

// New constructs a red-black tree using the compare function specified.
func New(cmp func(k1, k2 interface{}) int) Interface {
	t := &tree{compare: cmp}
	t.verify()
	return t
}

// Integer constructs a red-black tree by comparing integer key. Note that you
// must assure the key is integer type, or it will panic.
func Integer() Interface {
	cmp := func(k1, k2 interface{}) int {
		i1, i2 := k1.(int), k2.(int)
		if i1 == i2 {
			return 0
		} else if i1 < i2 {
			return -1
		} else {
			return 1
		}
	}
	return New(cmp)
}

// String constructs a red-black tree by comparing string key, Note that you
// must assure the key is string type, or it will panic.
func String() Interface {
	cmp := func(k1, k2 interface{}) int {
		s1, s2 := k1.(string), k2.(string)
		if s1 == s2 {
			return 0
		} else if s1 < s2 {
			return -1
		} else {
			return 1
		}
	}
	return New(cmp)
}

type color byte

const (
	colorRED color = iota
	colorBLACK
)

// node represents the red-black tree node, it wraps key and value together to
// make this red-black implemention to be useful associative map.
type node struct {
	k interface{}
	v interface{}
	c color
	l *node
	r *node
	p *node
}

// tree is an implemention of red-black tree
type tree struct {
	root    *node
	compare func(k1, k2 interface{}) int
}

// grandparent returns parent's parent of node n.
func grandparent(n *node) *node {
	return n.p.p
}

// sibling returns the other child of its parent. note that the sibling may be
// nil, if the parent has only one child.
func sibling(n *node) *node {
	if n == n.p.l {
		return n.p.r
	} else {
		return n.p.l
	}
}

// uncle returns the sibling of its parent. the uncle may also be nil, if the
// grandparent has only one child.
func uncle(n *node) *node {
	return sibling(n.p)
}

// getcolor returns color of tree node. Since all leaves are black and contain
// no data, we represent these empty leaves using nil, this property is
// implicity assured by always treating nil as black.
func getcolor(n *node) color {
	if n == nil {
		return colorBLACK
	} else {
		return n.c
	}
}

// verify enforces the following five properties, which provide a theoretical
// guarantee that the tree remains balanced. Note that many of these tests walk
// the tree, making them very expensive, for this reason we turn them on debug
// mode only.
func (t *tree) verify() {
	const debug = false
	if !debug {
		return
	}
	verify1(t.root)
	verify2(t.root)
	// property 3 is implicitly assured
	verify4(t.root)
	verify5(t.root)
}

// verify1 verifies each node is either red or black.
func verify1(n *node) {
	if getcolor(n) != colorRED && getcolor(n) != colorBLACK {
		panic("bad node color")
	}
	if n == nil {
		return
	}
	verify1(n.l)
	verify1(n.r)
}

// verify2 verifies root node is black
func verify2(root *node) {
	if getcolor(root) != colorBLACK {
		panic("root node is not black")
	}
}

// verify4 verifies every red node has two children, and both are black (or
// equivalently, the parent of every red node is black).
func verify4(n *node) {
	if getcolor(n) == colorRED {
		if getcolor(n.p) != colorBLACK {
			panic("red node parent is not black")
		}
		if getcolor(n.l) != colorBLACK {
			panic("red node left child is not black")
		}
		if getcolor(n.r) != colorBLACK {
			panic("red node right child is not black")
		}
	}
	if n == nil {
		return
	}
	verify4(n.l)
	verify4(n.r)
}

// verify5 verifies all paths from any given node to its leaf nodes contain the
// same number of black nodes. This one is the strickiest to verify; we do it by
// traversing the tree, incrementing a black node count as we go. The first item
// we reach a leaf we save the count. When we subsequently reach other leaves,
// we compare the count to this saved count.
func verify5(root *node) {
	pathBlackCount := -1
	verify5Helper(root, 0, &pathBlackCount)
}

func verify5Helper(n *node, blackCount int, pathBlackCount *int) {
	if getcolor(n) == colorBLACK {
		blackCount++
	}
	// we have reached a tree leaf
	if n == nil {
		if *pathBlackCount == -1 {
			*pathBlackCount = blackCount
		} else {
			if blackCount != *pathBlackCount {
				panic("verify5 failed")
			}
		}
		return
	}
	verify5Helper(n.l, blackCount, pathBlackCount)
	verify5Helper(n.r, blackCount, pathBlackCount)
}

//
// Properties 4 and 5 together guarantee that no path in the tree is more than
// about twice as long as any other path, which guarantees that it has O(log n)
// height.
//

// newNode is a helper function to allocate and initialize a new node.
func newNode(key, val interface{}, color color, left, right *node) *node {
	newn := &node{
		k: key,
		v: val,
		c: color,
		l: left,
		r: right,
		p: nil,
	}
	if left != nil {
		left.p = newn
	}
	if right != nil {
		right.p = newn
	}
	return newn
}

// Lookup returns the value of node, whose key equals the specified one. the ok
// is true if found or false otherwise.
func (t *tree) Lookup(key interface{}) (val interface{}, ok bool) {
	n := t.lookup(key)
	if n == nil {
		return nil, false
	}
	return n.v, true
}

// lookup do read-only search on a red-black tree by the given key, returns the
// node if success, or nil when not found.
func (t *tree) lookup(key interface{}) *node {
	n := t.root
	for n != nil {
		ret := t.compare(key, n.k)
		switch {
		case ret == 0:
			return n
		case ret < 0:
			n = n.l
		case ret > 0:
			n = n.r
		}
	}
	return n
}

// Both insertion and deletion rely on a fundamental operation for reducing tree
// height called a rotation. A rotation locally changes the structure of the
// tree without changing the in-order order of the sequence of values that it
// stores.
//
// We create two helper functions, one to perform a left rotation and one to
// perform a right rotation; each takes the highest node in the subtree as an
// argument.

func (t *tree) rotateLeft(n *node) {
	r := n.r
	t.replace(n, r)
	n.r = r.l
	if r.l != nil {
		r.l.p = n
	}
	r.l = n
	n.p = r
}

func (t *tree) rotateRight(n *node) {
	l := n.l
	t.replace(n, l)
	n.l = l.r
	if l.r != nil {
		l.r.p = n
	}
	l.r = n
	n.p = l
}

// replace is a helper function that cuts a node away from its parent,
// substituting a new node (or nil) in its place. It simplifies consistent
// updating of parent and child pointers. It needs the tree passed in because it
// may change which node is the root.
func (t *tree) replace(oldn *node, newn *node) {
	if oldn.p == nil {
		t.root = newn
	} else {
		if oldn == oldn.p.l {
			oldn.p.l = newn
		} else {
			oldn.p.r = newn
		}
	}
	if newn != nil {
		newn.p = oldn.p
	}
}

// Insert inserts a new value, we first insert it into the tree as we would into
// an ordinary binary search tree. If the key already exists, we just replace
// the value (since we're implementing an associative array). Otherwise, we find
// the place in the tree where the new pair belongs, then attach a newly created
// red node containing the value.
func (t *tree) Insert(key, val interface{}) {
	newn := newNode(key, val, colorRED, nil, nil)
	if t.root == nil {
		t.root = newn
	} else {
		n := t.root
		for {
			ret := t.compare(key, n.k)
			if ret == 0 {
				n.v = val
				return
			} else if ret < 0 {
				if n.l == nil {
					n.l = newn
					break
				} else {
					n = n.l
				}
			} else {
				if n.r == nil {
					n.r = newn
					break
				} else {
					n = n.r
				}
			}
		}
		newn.p = n
	}
	t.insert1(newn)
	t.verify()
}

// The problem is that the resulting tree may not satisfy our five red-black
// tree properties. The call to insert1() begins the process of correcting the
// tree so that it satisfies the properties once more.

// In this case, the new node is now the root of the tree. Since the root node
// must be black, and changing its color adds the same number of black nodes to
// every path, we simply recolor it black. Because only the root node has no
// parent, we can assume henceforth that the node has a parent.
func (t *tree) insert1(n *node) {
	if n.p == nil {
		n.c = colorBLACK
	} else {
		t.insert2(n)
	}
}

// In this case, the new node has a black parent. All the properties are still
// satisfied and we return.
func (t *tree) insert2(n *node) {
	if getcolor(n.p) == colorBLACK {
		return // tree is still valid
	} else {
		t.insert3(n)
	}
}

// In this case, the uncle node is red. We recolor the parent and uncle black
// and the grandparent red. However, the red grandparent node may now violate
// the red-black tree properties; we recursively invoke this procedure on it
// from case 1 to deal with this.
func (t *tree) insert3(n *node) {
	if getcolor(uncle(n)) == colorRED {
		n.p.c = colorBLACK
		uncle(n).c = colorBLACK
		grandparent(n).c = colorRED
		t.insert1(grandparent(n))
	} else {
		t.insert4(n)
	}
}

// In this case, we deal with two cases that are mirror images of one another:
//
//   1. The new node is the right child of its parent and the parent is the left
//      child of the grandparent. In this case we rotate left about the parent.
//
//   2. The new node is the left child of its parent and the parent is the right
//      child of the grandparent. In this case we rotate right about the parent.
//
// Neither of these fixes the properties, but they put the tree in the correct
// form to apply case 5.
func (t *tree) insert4(n *node) {
	if n == n.p.r && n.p == grandparent(n).l {
		t.rotateLeft(n.p)
		n = n.l
	} else if n == n.p.l && n.p == grandparent(n).r {
		t.rotateRight(n.p)
		n = n.r
	}
	t.insert5(n)
}

// In this final case, we deal with two cases that are mirror images of one
// another:
//
//   1. The new node is the left child of its parent and the parent is the left
//      child of the grandparent. In this case we rotate right about the
//      grandparent.
//
//   2. The new node is the right child of its parent and the parent is the
//      right child of the grandparent. In this case we rotate left about the
//      grandparent.
//
// Now the properties are satisfied and all cases have been covered.
func (t *tree) insert5(n *node) {
	n.p.c = colorBLACK
	grandparent(n).c = colorRED
	if n == n.p.l && n.p == grandparent(n).l {
		t.rotateRight(grandparent(n))
	} else if n == n.p.r && n.p == grandparent(n).r {
		t.rotateLeft(grandparent(n))
	}
}

// Delete begins by finding the node to be deleted with lookup() and deleting it
// precisely as we would in a binary search tree. There are two cases for
// removal, depending on whether the node to be deleted has at most one, or two
// non-leaf children. A node with at most one non-leaf children, we copy the
// value from the in-order predecessor (the maximum or the rightmost element in
// the left subtree) into the node to be deleted, and then we delete the
// predecessor node, which was only one non-leaf child. This same predecessor
// also also works in a red-black tree without affecting any properties.
func (t *tree) Delete(key interface{}) {
	n := t.lookup(key)
	if n == nil {
		return // key not found, do nothing
	}
	if n.l != nil && n.r != nil {
		// copy key/value from predecessor and then delete it instead
		pred := rightmost(n.l)
		n.k = pred.k
		n.v = pred.v
		n = pred
	}
	var child *node
	if n.l == nil {
		child = n.r
	} else if n.r == nil {
		child = n.l
	}
	if getcolor(n) == colorBLACK {
		n.c = getcolor(child)
		t.delete1(n)
	}
	t.replace(n, child)
	if n.p == nil && child != nil { // root should be black
		child.c = colorBLACK
	}
	t.verify()
}

// rightmost helper function just walks right until it reaches the last
// non-leaf.
func rightmost(n *node) *node {
	if n == nil {
		panic("nil node")
	}
	for n.r != nil {
		n = n.r
	}
	return n
}

// However, before deleting the node, we must ensure that doing so does not
// violate the red-black tree properties. If the node we delete is black, and we
// cannot change its child from red to black to compensate, then we would have
// one less black node on every path through the child node. We must adjust the
// tree around the node being deleted to compensate.

// In this case, N has become the root node. The deletion removed one black node
// from every path, so no properties are violated.
func (t *tree) delete1(n *node) {
	if n.p == nil {
		return
	} else {
		t.delete2(n)
	}
}

// N has a red sibling. In this case we exchange the colors of the parent and
// sibling, then rotate about the parent so that the sibling becomes the parent
// of its former parent. This does not restore the tree properties, but reduces
// the problem to one of the remaining cases.
func (t *tree) delete2(n *node) {
	if getcolor(sibling(n)) == colorRED {
		n.p.c = colorRED
		sibling(n).c = colorBLACK
		if n == n.p.l {
			t.rotateLeft(n.p)
		} else {
			t.rotateRight(n.p)
		}
	}
	t.delete3(n)
}

// In this case N's parent, sibling, and sibling's children are black. In this
// case we paint the sibling red. Now all paths passing through N's parent have
// one less black node than before the deletion, so we must recursively run this
// procedure from case 1 on N's parent.
func (t *tree) delete3(n *node) {
	if getcolor(n.p) == colorBLACK &&
		getcolor(sibling(n)) == colorBLACK &&
		getcolor(sibling(n).l) == colorBLACK &&
		getcolor(sibling(n).r) == colorBLACK {
		sibling(n).c = colorRED
		t.delete1(n.p)
	} else {
		t.delete4(n)
	}
}

// N's sibling and sibling's children are black, but its parent is red. We
// exchange the colors of the sibling and parent; this restore the tree
// properties.
func (t *tree) delete4(n *node) {
	if getcolor(n.p) == colorRED &&
		getcolor(sibling(n)) == colorBLACK &&
		getcolor(sibling(n).l) == colorBLACK &&
		getcolor(sibling(n).r) == colorBLACK {
		sibling(n).c = colorRED
		n.p.c = colorBLACK
	} else {
		t.delete5(n)
	}
}

// There are two cases handled here which are mirror images of one another:
//
//   1. N's sibling S is black, S's left child is red, S's right child is black,
//      and N is the left child of its parent. We exchange the colors of S and
//      its left sibling and rotate right at S.
//
//   2. N's sibling S is black, S's right child is red, S's left child is black,
//      and N is the right child of its parent. We exchange the colors of S and
//      its right sibling and rotate left at S.
func (t *tree) delete5(n *node) {
	if n == n.p.l &&
		getcolor(sibling(n)) == colorBLACK &&
		getcolor(sibling(n).l) == colorRED &&
		getcolor(sibling(n).r) == colorBLACK {
		sibling(n).c = colorRED
		sibling(n).l.c = colorBLACK
		t.rotateRight(sibling(n))
	} else if n == n.p.r &&
		getcolor(sibling(n)) == colorBLACK &&
		getcolor(sibling(n).r) == colorRED &&
		getcolor(sibling(n).l) == colorBLACK {
		sibling(n).c = colorRED
		sibling(n).r.c = colorBLACK
		t.rotateLeft(sibling(n))
	}
	t.delete6(n)
}

// There are two cases handled here which are mirror images of one another:
//
//   1. N's sibling S is black, S's right child is red, and N is the left child of
//      its parent. We exchange the colors of N's parent and sibling, make S's
//      right child black, then rotate left at N's parent.
//
//   2. N's sibling S is black, S's left child is red, and N is the right child of
//      its parent. We exchange the colors of N's parent and sibling, make S's left
//      child black, then rotate right at N's parent.
//
// This accomplishes three things at once:
//
//   1. We add a black node to all paths through N, either by adding a black S to
//      those paths or by recoloring N's parent black.
//
//   2. We remove a black node from all paths through S's red child, either by
//      removing P from those paths or by recoloring S.
//
//   3. We recolor S's red child black, adding a black node back to all paths
//      through S's red child.
//
// S's left child has become a child of N's parent during the rotation and so is
// unaffected.
//
// Again, the function calls all use tail recursion, so the algorithm is
// in-place. Additionally, no recursive calls will be made after a rotation, so
// no more than three rotations are made.
func (t *tree) delete6(n *node) {
	sibling(n).c = getcolor(n.p)
	n.p.c = colorBLACK
	if n == n.p.l {
		sibling(n).r.c = colorBLACK
		t.rotateLeft(n.p)
	} else if n == n.p.r {
		sibling(n).l.c = colorBLACK
		t.rotateRight(n.p)
	}
}
