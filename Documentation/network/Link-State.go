// https://en.wikipedia.org/wiki/Link-state_routing_protocol
//
// Copyright (C) to Park Zhou <ideapark@139.com>
//
//go:generate go run Link-State.go
package main

import (
	"fmt"
	"slices"
)

type (
	W int
	V int
	E struct {
		v [2]V
		w W
	}
	G []E
)

// Weighted Graph
var g = G{
	{[2]V{'u', 'x'}, 1},
	{[2]V{'x', 'y'}, 1},
	{[2]V{'y', 'z'}, 2},
	{[2]V{'z', 'w'}, 5},
	{[2]V{'w', 'v'}, 3},
	{[2]V{'v', 'u'}, 2},
	{[2]V{'x', 'v'}, 2},
	{[2]V{'x', 'w'}, 3},
	{[2]V{'y', 'w'}, 1},
	{[2]V{'u', 'w'}, 5},
}

var (
	// Source node u
	u = V('u')

	// Subset of nodes; v is in N if the least-cost path
	// from the source node u to v is known
	N = []V{u}

	// Cost of the least-cost path from source node u to
	// destination v
	D = map[V]W{u: 0}

	// Previous node (neighbor of v) along the current least-cost
	// path from source node u to v
	P = map[V]V{u: u}
)

func inN(v V) bool {
	return slices.Contains(N, v)
}

func show() {
	for _, v := range N {
		fmt.Printf("(%d):", D[v])
		for {
			fmt.Printf("%c", v)
			if v == u {
				break
			}
			fmt.Printf("←")
			v = P[v]
		}
		fmt.Println()
	}
}

// Link-State (LS) Algorithm for Source Node u
//
//	 1: Initialization:
//	 2:   N' = {u}
//	 3:   for all nodes v
//	 4:     if v is a neighbor of u
//	 5:       then D(v) = c(u,v)
//	 6:     else
//	 7:       D(v) = ∞
//	 8:
//	 9: Loop
//	10:  find w not in N' such that D(w) is a minimum
//	11:  add w to N'
//	12:  update D(v) for each neighbor v of w and not in N':
//	13:    D(v) = min(D(v), D(w)+c(w,v))
//	14: Until N' = N
func LinkState() {
	//
	// Spanning neighbors of source node u
	//
	for _, e := range g {
		var (
			v0 = e.v[0]
			v1 = e.v[1]
			w  = e.w
		)
		switch {
		case u == v0:
			D[v1] = w
			P[v1] = u
		case u == v1:
			D[v0] = w
			P[v0] = u
		}
	}

	//
	// Iterate until N does not grow any more
	//
Done:
	for {
		var (
			v V = u
			w W = 0
		)

	Next:
		for _v, _w := range D {
			if inN(_v) {
				continue Next
			}

			if w == 0 || _w < w {
				v = _v
				w = _w
			}
		}

		if inN(v) {
			break Done
		}

		N = append(N, v)

		// Spanning neighbors of node v, provided that D[v] is
		// a minimum
		for _, e := range g {
			var (
				v0 = e.v[0]
				v1 = e.v[1]
				w  = e.w
			)
			switch {
			case v == v0:
				if inN(v1) {
					continue
				}
				_w, ok := D[v1]
				switch {
				case !ok, // create
					ok && _w > D[v]+w: // update
					D[v1] = D[v] + w
					P[v1] = v
				}
			case v == v1:
				if inN(v0) {
					continue
				}
				_w, ok := D[v0]
				switch {
				case !ok, // create
					ok && _w > D[v]+w: // update
					D[v0] = D[v] + w
					P[v0] = v
				}
			}
		}
	}
}

func main() {
	LinkState()
	show()
}
