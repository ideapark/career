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
	N int
	E struct {
		n [2]N
		w W
	}
	G []E
)

// Weighted Graph
var g = G{
	{[2]N{'u', 'x'}, 1},
	{[2]N{'x', 'y'}, 1},
	{[2]N{'y', 'z'}, 2},
	{[2]N{'z', 'w'}, 5},
	{[2]N{'w', 'v'}, 3},
	{[2]N{'v', 'u'}, 2},
	{[2]N{'x', 'v'}, 2},
	{[2]N{'x', 'w'}, 3},
	{[2]N{'y', 'w'}, 1},
	{[2]N{'u', 'w'}, 5},
}

var (
	// Source node U
	U = N('u')

	// Subset of nodes; n is in Nprime if the least-cost path from
	// the source node u to n is known
	Nprime = []N{U}

	// Cost of the least-cost path from source node u to
	// destination n
	D = map[N]W{U: 0}

	// Previous node (neighbor of n) along the current least-cost
	// path from source node u to n
	P = map[N]N{U: U}
)

func inNprime(n N) bool {
	return slices.Contains(Nprime, n)
}

func show() {
	fmt.Println("WEIGHT\tPATH")
	for _, n := range Nprime {
		fmt.Printf("(%d):\t", D[n])
		for {
			fmt.Printf("%c", n)
			if n == U {
				break
			}
			fmt.Printf("←")
			n = P[n]
		}
		fmt.Println()
	}
}

// Link-State (LS) Algorithm for Source Node u
//
//	 1: Initialization:
//	 2:   Nprime = {u}
//	 3:   for all nodes n
//	 4:     if n is a neighbor of u
//	 5:       then D(n) = cost(u,n)
//	 6:     else
//	 7:       D(n) = ∞
//	 8:
//	 9: Loop
//	10:  find w not in Nprime such that D(w) is a minimum
//	11:  add w to Nprime
//	12:  update D(n) for each neighbor n of w and not in Nprime:
//	13:    D(n) = min(D(n), D(w)+c(w,n))
//	14: Until Nprime = N
func LinkState() {
	//
	// Spanning neighbors of source node u
	//
	for _, e := range g {
		var (
			n0 = e.n[0]
			n1 = e.n[1]
			w  = e.w
		)
		switch {
		case U == n0:
			D[n1] = w
			P[n1] = U
		case U == n1:
			D[n0] = w
			P[n0] = U
		}
	}

	//
	// Iterate until Nprime does not grow any more
	//
Done:
	for {
		var (
			n N = U
			w W = 0
		)

	Next:
		for _n, _w := range D {
			if inNprime(_n) {
				continue Next
			}

			if w == 0 || _w < w {
				n = _n
				w = _w
			}
		}

		if inNprime(n) {
			break Done
		}

		Nprime = append(Nprime, n)

		// Spanning neighbors of node n, provided that D[n] is
		// a minimum
		for _, e := range g {
			var (
				n0 = e.n[0]
				n1 = e.n[1]
				w  = e.w
			)
			switch {
			case n == n0:
				if inNprime(n1) {
					continue
				}
				_w, ok := D[n1]
				switch {
				case !ok, // create
					ok && _w > D[n]+w: // update
					D[n1] = D[n] + w
					P[n1] = n
				}
			case n == n1:
				if inNprime(n0) {
					continue
				}
				_w, ok := D[n0]
				switch {
				case !ok, // create
					ok && _w > D[n]+w: // update
					D[n0] = D[n] + w
					P[n0] = n
				}
			}
		}
	}
}

func main() {
	LinkState()
	show()
}
