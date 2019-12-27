// EqualFold reports whether s and t, interpreted as UTF-8 strings, are equal
// under Unicode case-folding.
package main

import (
	"bytes"
	"fmt"
)

func main() {
	fmt.Println(bytes.EqualFold([]byte("Go"), []byte("go")))
}
