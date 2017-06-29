package main

import (
	"fmt"
)

func main() {
	done := make(chan bool)
	values := []string{"a", "b", "c"}

	// BUG: goroutines access the same v
	for _, v := range values {
		go func() {
			fmt.Println(v)
			done <- true
		}()
	}
	for _ = range values {
		<-done
	}

	// OK: v will escape to heap. why?
	for _, v := range values {
		go func(u string) {
			fmt.Println(u)
			done <- true
		}(v)
	}
	for _ = range values {
		<-done
	}

	// OK: idiomatic go, v will escape to heap
	for _, v := range values {
		v := v
		go func() {
			fmt.Println(v)
			done <- true
		}()
	}
	for _ = range values {
		<-done
	}
}
