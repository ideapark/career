// IndexAny interprets s as a sequence of UTF-8-encoded Unicode code points. It
// returns the byte index of the first occurrence in s of any of the Unicode
// code points in chars. It returns -1 if chars is empty or if there is no code
// point in common.
package main

import (
	"bytes"
	"fmt"
)

func main() {
	fmt.Println(bytes.IndexAny([]byte("chicken"), "aeiouy"))
	fmt.Println(bytes.IndexAny([]byte("crwth"), "aeiouy"))
}
