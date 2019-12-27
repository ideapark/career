package main

import (
	"fmt"
	"runtime"
	"time"
)

func f(left chan<- int, right <-chan int) {
	for c := range right {
		left <- 1 + c
	}
	close(left)
}

func feed(m int, c chan<- int) {
	for i := 0; i < m; i++ {
		c <- m
	}
	close(c)
}

func main() {
	runtime.GOMAXPROCS(runtime.NumCPU())
	const n = 500000
	const m = 200

	// first we construct an array of n+1 channels each being a 'chan int'
	var channels [n + 1]chan int
	for i := range channels {
		channels[i] = make(chan int)
	}
	fmt.Printf("Pipeline of %d stages\n", n)
	fmt.Printf("  starting with %d messages,\n", m)
	fmt.Printf("  total %d steps,\n", n*m)
	start := time.Now()

	// now we wire n goroutine in a chan
	for i := 0; i < n; i++ {
		go f(channels[i], channels[i+1])
	}

	// insert some values into the right-hand end
	go feed(m, channels[n])

	// pick up the values emerging from the left-hand end
	var x int
	for c := range channels[0] {
		x = c
	}
	nanos := time.Since(start).Nanoseconds()
	tpl := nanos / (n * m)

	fmt.Printf("Last number was %d\n", x)
	fmt.Printf("Time: %dms, time per step: %dns\n", nanos/100000, tpl)
}
