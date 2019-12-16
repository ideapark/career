package main

import (
	"runtime/debug"
)

func wouldPanic() {
	panic("I am dead.")
}

func main() {
	defer func() {
		if err := recover(); err != nil {
			debug.PrintStack()
		}
	}()
	wouldPanic()
}
