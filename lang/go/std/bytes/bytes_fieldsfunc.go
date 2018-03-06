// FieldsFunc interprets s as a sequence of UTF-8-encoded code points. It splits
// the slice s at each run of code points c satisfying f(c) and returns a slice
// of subslices of s. If all code points in s satisfy f(c), or len(s) == 0, an
// empty slice is returned. FieldsFunc makes no guarantees about the order in
// which it calls f(c). If f does not return consistent results for a given c,
// FieldsFunc may crash.
package main

import (
	"bytes"
	"fmt"
	"unicode"
)

func main() {
	f := func(c rune) bool {
		return !unicode.IsLetter(c) && !unicode.IsNumber(c)
	}
	fmt.Printf("Fields are: %q", bytes.FieldsFunc([]byte(" foo1;bar2,baz3..."), f))
}
