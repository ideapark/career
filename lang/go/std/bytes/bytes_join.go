// Join concatenates the elements of s to create a new byte slice. The separator
// sep is placed between elements in the resulting slice.
package main

import (
	"bytes"
	"fmt"
)

func main() {
	s := [][]byte{[]byte("foo"), []byte("bar"), []byte("baz")}
	fmt.Printf("%s", bytes.Join(s, []byte(",")))
}
