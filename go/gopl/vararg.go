package main

import (
	"fmt"
)

func vprint(a ...int) {
	for i := range a {
		a[i] += 10 // we can change the under array of the variable arg slice.
	}
	fmt.Printf("%T, %v\n", a, a)
}

func main() {
	vprint(1, 2, 3, 4) // variable args is just slice of same type array

	a := [3]int{1, 2, 3}
	vprint(a[:]...) // you must get slice first
}
