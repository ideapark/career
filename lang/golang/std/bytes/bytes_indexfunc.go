// IndexFunc interprets s as a sequence of UTF-8-encoded code points. It returns
// the byte index in s of the first Unicode code point satisfying f(c), or -1 if
// none do.
package main

import (
	"bytes"
	"fmt"
	"unicode"
)

func main() {
	f := func(c rune) bool {
		return unicode.Is(unicode.Han, c)
	}
	fmt.Println(bytes.IndexFunc([]byte("Hello, 世界"), f))
	fmt.Println(bytes.IndexFunc([]byte("Hello, world"), f))
}
