// SplitAfterN slices s into subslices after each instance of sep and returns a
// slice of those subslices. If sep is empty, SplitAfterN splits after each
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
	fmt.Printf("%q\n", bytes.SplitAfterN([]byte("a,b,c"), []byte(","), 2))
}
