// Count counts the number of non-overlapping instances of sep in s. If sep is
// an empty slice, Count returns 1 + the number of UTF-8-encoded code points in
// s.
package main

import (
	"bytes"
	"fmt"
)

func main() {
	fmt.Println(bytes.Count([]byte("cheese"), []byte("e")))
	fmt.Println(bytes.Count([]byte("five"), []byte(""))) // before & after each rune
}
