// LastIndex returns the index of the last instance of sep in s, or -1 if sep is
// not present in s.
package main

import (
	"bytes"
	"fmt"
)

func main() {
	fmt.Println(bytes.Index([]byte("go gopher"), []byte("go")))
	fmt.Println(bytes.LastIndex([]byte("go gopher"), []byte("go")))
	fmt.Println(bytes.LastIndex([]byte("go gopher"), []byte("rodent")))
}
