// Fields interprets s as a sequence of UTF-8-encoded code points. It splits the
// slice s around each instance of one or more consecutive white space
// characters, as defined by unicode.IsSpace, returning a slice of subslices of
// s or an empty slice if s contains only white space.
package main

import (
	"bytes"
	"fmt"
)

func main() {
	fmt.Printf("Fields are: %q", bytes.Fields([]byte(" foo bar baz   ")))
}
