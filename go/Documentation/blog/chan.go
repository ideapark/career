// Channel's Axioms
//
// 1. A send to a nil channel blocks forever
// 2. A receive from a nil channel blocks forever
// 3. A send to a closed channel panic
// 4. A receive from a closed channel returns the zero value immediately

package main

import "fmt"

func main() {
	// A send to a nil channel blocks forever
	var c1 chan string
	c1 <- "let's get started" // deadlock

	// A receive from a nil channel blocks forever
	var c2 chan string
	<-c2 // deadlock

	// A send to a closed channel panics
	c3 := make(chan int, 100)
	go func() {
		for i := 0; i < 10; i++ {
			c3 <- i
		}
		close(c3)
	}()
	c3 <- 1

	// A receive from a closed channel returns the zero value immediately
	c4 := make(chan int, 3)
	go func() {
		for i := 0; i < 10; i++ {
			c4 <- i
		}
		close(c4)
	}()
	for i := 0; i < 100; i++ {
		fmt.Printf("%d", <-c4)
	}
}
