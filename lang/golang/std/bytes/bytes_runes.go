// Runes interprets s as a sequence of UTF-8-encoded code points. It returns a
// slice of runes (Unicode code points) equivalent to s.
package main

import (
	"bytes"
	"fmt"
)

func main() {
	rs := bytes.Runes([]byte("go gopher"))
	for _, r := range rs {
		fmt.Printf("%#U\n", r)
	}
}
