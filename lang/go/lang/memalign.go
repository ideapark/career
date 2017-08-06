package main

import (
	"fmt"
	"unsafe"
)

func main() {
	v := struct {
		a struct{}
	}{}

	fmt.Printf("v: %p, %d, %d\n", &v, unsafe.Sizeof(v), unsafe.Alignof(v))
	fmt.Printf("a: %p, %d, %d\n", &v, unsafe.Sizeof(v.a), unsafe.Alignof(v.a))
}
