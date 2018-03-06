// SplitN slices s into subslices separated by sep and returns a slice of the
// subslices between those separators. If sep is empty, SplitN splits after each
// UTF-8 sequence. The count determines the number of subslices to return:
//
// n > 0: at most n subslices; the last subslice will be the unsplit remainder.
// n == 0: the result is nil (zero subslices)
// n < 0: all subslices
package main

import (
	"bytes"
	"fmt"
)

func main() {
	fmt.Printf("%q\n", bytes.SplitN([]byte("a,b,c"), []byte(","), 2))
	z := bytes.SplitN([]byte("a,b,c"), []byte(","), 0)
	fmt.Printf("%q (nil = %v)\n", z, z == nil)
}
