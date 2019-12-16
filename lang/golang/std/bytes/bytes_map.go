// Map returns a copy of the byte slice s with all its characters modified
// according to the mapping function. If mapping returns a negative value, the
// character is dropped from the byte slice with no replacement. The characters
// in s and the output are interpreted as UTF-8-encoded code points.
package main

import (
	"bytes"
	"fmt"
)

func main() {
	rot13 := func(r rune) rune {
		switch {
		case r >= 'A' && r <= 'z':
			return 'A' + (r-'A'+13)%26
		case r >= 'a' && r <= 'z':
			return 'a' + (r-'a'+13)%26
		}
		return r
	}
	fmt.Printf("%s", bytes.Map(rot13, []byte("Twas brilling and the slithy gopher...")))
}
