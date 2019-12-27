package main

import (
	"fmt"
	"hash/crc32"
	"io"
	"os"
)

// os.Stdout is an io.Writer

func main() {
	h := crc32.NewIEEE() // returns a hash.Hash32 which is a Hash which is an io.Writer
	w := io.MultiWriter(h, os.Stdout)
	fmt.Fprintf(w, "Hello, 世界\n")
	fmt.Printf("hash=%#x\n", h.Sum32())
}
