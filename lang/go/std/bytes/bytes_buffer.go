// A Buffer is a variable-sized buffer of bytes with Read and Write methods. The
// zero value for Buffer is an empty buffer ready to use.
package main

import (
	"bytes"
	"fmt"
	"os"
)

func main() {
	var b bytes.Buffer // A buffer needs no initialization
	b.Write([]byte("Hello "))
	fmt.Fprintf(&b, "world!")
	b.WriteTo(os.Stdout)
}
