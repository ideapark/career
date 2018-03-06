// Equal returns a boolean reporting whether a and b are the same length and
// contain the same bytes. A nil argument is equivalent to an empty slice.
package main

import (
	"bytes"
	"fmt"
)

func main() {
	fmt.Println(bytes.Equal([]byte("Go"), []byte("Go")))
	fmt.Println(bytes.Equal([]byte("Go"), []byte("C++")))
}
