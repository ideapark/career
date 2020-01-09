//
// GODEBUG=gctrace=1 go run gctrace.go
//
package main

func alloc() {
	_ = make([]byte, 1<<20)
}

func main() {
	for i := 0; i < 10000; i++ {
		alloc()
	}
}
