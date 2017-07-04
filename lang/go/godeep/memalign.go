package main

import (
	"fmt"
	"unsafe"
)

func main() {
	v := struct {
		a struct{}
	}{}

	fmt.Printf("%p, %d, %d\n", &v, unsafe.Sizeof(v), unsafe.Alignof(v))
}
