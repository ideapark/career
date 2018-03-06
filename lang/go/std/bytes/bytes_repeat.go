// Repeat returns a new byte slice consisting of count copies of b.
// It panics if count is negative or if the result of (len(b) * count)
// overflows.
package main

import (
	"bytes"
	"fmt"
)

func main() {
	fmt.Printf("ba%s", bytes.Repeat([]byte("na"), 2))
}
