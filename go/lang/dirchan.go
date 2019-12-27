package main

import (
	"sync"
)

func main() {
	var wg sync.WaitGroup
	wg.Add(2)

	c := make(chan int)
	var snd chan<- int = c
	var rcv <-chan int = c

	// receiver
	go func() {
		defer wg.Done()
		for x := range rcv {
			println(x)
		}
	}()

	// sender
	go func() {
		defer wg.Done()
		defer close(c)
		for i := 0; i < 3; i++ {
			snd <- i
		}
	}()

	wg.Wait()
}
