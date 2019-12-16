// Index returns the index of the first instance of sep in s, or -1 if sep is
// not present in s.
package main

import (
	"bytes"
	"fmt"
)

func main() {
	fmt.Println(bytes.Index([]byte("chiken"), []byte("ken")))
	fmt.Println(bytes.Index([]byte("chiken"), []byte("dmr")))
}
