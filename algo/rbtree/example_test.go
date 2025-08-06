// Copyright 2020 © Park Zhou <ideapark@petalmail.com>

package rbtree

import (
	"fmt"
)

func ExampleInteger() {
	tree := Integer()
	for i := range 5 {
		tree.Insert(i, i)
	}
	for i := range 5 {
		if i%2 == 0 {
			tree.Delete(i)
		}
	}
	for i := range 5 {
		v, ok := tree.Lookup(i)
		if i%2 != 0 && ok {
			fmt.Println(v)
		}
	}

	// Output:
	// 1
	// 3
}

func ExampleString() {
	tree := String()
	words := []string{"the", "quick", "fox", "jumped", "over", "the", "lazy", "dog"}
	for _, w := range words {
		tree.Insert(w, w)
	}
	for i, w := range words {
		if i%2 == 0 {
			tree.Delete(w)
		}
	}
	for i, w := range words {
		v, ok := tree.Lookup(w)
		if i%2 != 0 && ok {
			fmt.Println(v)
		}
	}

	// Output:
	// quick
	// jumped
	// dog
}

func ExampleNew() {
	// A user defined type used as red-black tree key
	type key struct {
		i int
		s string
	}
	cmp := func(k1, k2 any) int {
		d1, d2 := k1.(key), k2.(key)
		if d1.i == d2.i {
			if d1.s == d2.s {
				return 0
			} else if d1.s < d2.s {
				return -1
			} else {
				return 1
			}
		} else if d1.i < d2.i {
			return -1
		} else {
			return 1
		}
	}
	tree := New(cmp)
	words := []string{"the", "quick", "fox", "jumped", "over", "the", "lazy", "dog"}
	for i, w := range words {
		tree.Insert(key{i, w}, w)
	}
	for i, w := range words {
		if i%2 == 0 {
			tree.Delete(key{i, w})
		}
	}
	for i, w := range words {
		v, ok := tree.Lookup(key{i, w})
		if i%2 != 0 && ok {
			fmt.Println(v)
		}
	}

	// Output:
	// quick
	// jumped
	// the
	// dog
}
