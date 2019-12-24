package main

import (
	"fmt"
	"unsafe"
)

func main() {
	// makemap implements a Go map creation make(map[k]v, hint)
	// If the compiler has determined that the map or the first
	// bucket can be created on the stack, h and/or bucket may
	// be non-nil. If h != nil, the map can be created directly
	// in h. If bucket != nil, bucket can be used as the first
	// bucket.
	//    func runtime.makemap(t *maptype, hint int64, h *hmap, bucket unsafe.Pointer) *hmap
	var m map[int]int
	var p uintptr
	fmt.Println(unsafe.Sizeof(m), unsafe.Sizeof(p)) // 8 8 (linux/amd64)
}
