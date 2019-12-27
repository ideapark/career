// SplitAfter slices s into all subslices after each instance of sep and returns
// a slice of those subslices. If sep is empty, SplitAfter splits after each
// UTF-8 sequence. It is equivalent to SplitAfterN with a count of -1.
package main

import (
	"bytes"
	"fmt"
)

func main() {
	fmt.Printf("%q\n", bytes.SplitAfter([]byte("a,b,c"), []byte(",")))
}
