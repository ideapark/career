package main

import (
	"time"
)

func main() {
	exit := make(chan struct{})

	go func() {
		time.Sleep(time.Second)
		println("goroutine done.")
		close(exit) // close channel signal other waiting goroutines.
	}()

	println("main ...")
	<-exit
	println("main exit.")
}
