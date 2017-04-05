package main

import (
	"crypto/sha1"
	"fmt"
)

func main() {
	data := []byte("This page intentionally left blank.")
	fmt.Printf("% X", sha1.Sum(data))
}
