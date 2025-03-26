// https://en.wikipedia.org/wiki/Distance-vector_routing_protocol
//
// Copyright (C) to Park Zhou <ideapark@139.com>
//
// Distance-Vector (DV) Algorithm
// at each node, x:
//
//	1: Initialization:
//	2:     for all destinations y in N:
//	3:       Dx(y) = c(x,y)                 /* if y is not a neighbor then c(x,y)= ∞ */
//	4:     for each neighbor w
//	5:       Dw(y) = ? for all destinations y in N
//	6:     for each neighbor w
//	7:       send distance vector Dx = [Dx(y): y in N] to w
//	8:
//	9: Loop
//	10:     wait (until I see a link cost change to some neighbor w or
//	11:           until I receive a distance vector from some neighbor w)
//	12:
//	13:     for each y in N:
//	14:       Dx(y) = min_v{c(x,v)+Dv(y)}
//	15:
//	16: if Dx(y) changed for any destination y
//	17:     send distance vector Dx = [Dx(y): y in N] to all neighbor
//	18:
//	19: forever
//
//go:generate go run Distance-Vector.go
package main

import (
	"time"
)

type (
	C int // cost
	N int // node
	D map[N]C
)

// Initialization:
//
//	Dx(x) = 0
//	Dx(y) = cost(x,y)  for y is neighbor of x
//	Dx(y) = ∞          for y is not neighbor of x
var dv0 = map[N]D{
	'x': {
		'x': 0,
		'y': 2,
		'z': 7,
	},
	'y': {
		'y': 0,
		'x': 2,
		'z': 1,
	},
	'z': {
		'z': 0,
		'x': 7,
		'y': 1,
	},
}

var links = map[string]chan D{
	"xy": make(chan D),
	"yz": make(chan D),
	"zx": make(chan D),
}

func dvnode(in []<-chan D, out []chan<- D) {

}

func DistnaceVector() {
	// Node 'x'
	go dvnode(
		[]<-chan D{links["xy"], links["zx"]},
		[]chan<- D{links["xy"], links["zx"]},
	)

	// Node 'y'
	go dvnode(
		[]<-chan D{links["yz"], links["xy"]},
		[]chan<- D{links["yz"], links["xy"]},
	)

	// Node 'z'
	go dvnode(
		[]<-chan D{links["zx"], links["yz"]},
		[]chan<- D{links["zx"], links["yz"]},
	)

Done:
	for {

		break Done
	}
}

func main() {
	DistnaceVector()

	time.Sleep(5 * time.Second)
}
