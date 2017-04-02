package main

import (
	"bytes"
	"fmt"
)

func main() {
	fmt.Println(bytes.Index([]byte("chiken"), []byte("ken")))
	fmt.Println(bytes.Index([]byte("chiken"), []byte("dmr")))
}
