// Replace returns a copy of the slice s with the first n non-overlapping
// instances of old replaced by new. If old is empty, it matches at the
// beginning of the slice and after each UTF-8 sequence, yielding up to k+1
// replacements for a k-rune slice. If n < 0, there is no limit on the number of
// replacements.
package main

import (
	"bytes"
	"fmt"
)

func main() {
	fmt.Printf("%s\n", bytes.Replace([]byte("oink oink oink"), []byte("k"), []byte("ky"), 2))
	fmt.Printf("%s\n", bytes.Replace([]byte("oink oink oink"), []byte("oink"), []byte("moo"), -1))
}
