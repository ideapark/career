package main

import (
	"fmt"
)

func main() {
	const (
		read byte = 1 << iota
		write
		exec
		freeze
	)

	a := read | write | freeze
	b := read | freeze | exec
	c := a &^ b

	fmt.Printf("%04b &^ %04b = %04b", a, b, c)
}
