package main

import (
	"runtime"
)

func main() {
	run := make(chan struct{})

	go func() {
		run <- struct{}{}
		for {
		}
	}()

	<-run

	// runtime.GC() needs STW
	runtime.GC()

	println("Will never reach here <= go1.14")
}
