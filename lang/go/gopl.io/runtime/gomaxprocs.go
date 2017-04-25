package main

import (
	"fmt"
	"runtime"
)

func main() {
	runtime.GOMAXPROCS(1) // set GOMAXPROCS to 2 will get parallelism
	for {
		go func() {
			fmt.Print(0)
		}()
		fmt.Print(1)
	}
}
