// Copyright 2020 © Park Zhou <ideapark@petalmail.com>

package rbtree

import (
	"testing"
)

func TestInteger(t *testing.T) {
	tree := Integer()
	for i := range 100 {
		tree.Insert(i, i)
	}
	for i := range 100 {
		v, ok := tree.Lookup(i)
		if !ok {
			t.Fatalf("do not find %d", i)
		}
		if i != v {
			t.Fatalf("expect: %d, got: %d", i, v)
		}
	}
	for i := range 100 {
		if i%2 == 0 {
			tree.Delete(i)
		}
	}
	for i := range 100 {
		if i%2 == 0 {
			v, ok := tree.Lookup(i)
			if ok {
				t.Fatalf("expect not found: %d, but found: %d", i, v)
			}
		}
	}
}

func TestString(t *testing.T) {
	words := []string{"the", "quick", "fox", "jumped", "over", "the", "lazy", "dog"}
	tree := String()
	for _, w := range words {
		tree.Insert(w, w)
	}
	for _, w := range words {
		v, ok := tree.Lookup(w)
		if !ok {
			t.Fatalf("do not find %s", w)
		}
		if w != v {
			t.Fatalf("expect: %s, got: %s", w, v)
		}
	}
	for i, w := range words {
		if i%2 == 0 {
			tree.Delete(w)
		}
	}
	for i, w := range words {
		if i%2 == 0 {
			v, ok := tree.Lookup(w)
			if ok {
				t.Fatalf("expect not found: %s, but found: %s", w, v)
			}
		}
	}
}
