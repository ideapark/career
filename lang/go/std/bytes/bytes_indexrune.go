// IndexRune interprets s as a sequence of UTF-8-encoded code points. It returns
// the byte index of the first occurrence in s of the given rune. It returns -1
// if rune is not present in s. If r is utf8.RuneError, it returns the first
// instance of any invalid UTF-8 byte sequence.
package main

import (
	"bytes"
	"fmt"
)

func main() {
	fmt.Println(bytes.IndexRune([]byte("chicken"), 'k'))
	fmt.Println(bytes.IndexRune([]byte("chicken"), 'd'))
}
