package main

import (
	"fmt"
)

type N int

func (n N) value() {
	n++
	fmt.Printf("v: %p, %v\n", &n, n)
}

func (n *N) pointer() {
	(*n)++
	fmt.Printf("p: %p, %v\n", n, *n)
}

func main() {
	var v N = 25
	p := &v

	v.value()
	p.pointer()

	// compiler will convert between T and *T automatically
	v.pointer()
	p.value()

	fmt.Printf("a: %p, %v\n", &v, v)
}
