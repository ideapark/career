package main

import (
	"time"
)

func main() {
	m := make(map[string]int)

	// write
	go func() {
		for {
			m["a"] += 1
			time.Sleep(time.Microsecond)
		}
	}()

	// read
	go func() {
		for {
			_ = m["b"]
			time.Sleep(time.Microsecond)
		}
	}()

	// pause main goroutine
	select {}
}

/*
go run -race syncmap.go
*/
