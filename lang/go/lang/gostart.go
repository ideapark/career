package main

import (
	"time"
)

var c int

func counter() int {
	c++
	return c
}

func main() {
	a := 100

	// goroutine's args will be evaluated and copied right now.
	go func(x, y int) {
		time.Sleep(time.Second)
		println("go:", x, y)
	}(a, counter())

	a += 100
	println("main:", a, counter())

	time.Sleep(3 * time.Second)
}
