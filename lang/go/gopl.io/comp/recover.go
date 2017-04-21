package main

import (
	"fmt"
	"math/rand"
)

type bailout struct{}

func main() {
	defer func() {
		switch p := recover(); p {
		case nil:
			// no panic
		case bailout{}:
			// "expected" panic
			fmt.Println("panic recovered.")
		default:
			// unexpected panic; carry on panicking
			panic(p)
		}
	}()
	randPanic()
}

func randPanic() {
	rand.Seed(42) // Try changing this number!
	switch rand.Intn(4) {
	case 0:
		panic("")
	case 1, 2:
		panic(bailout{})
	default:
		fmt.Printf("work well")
	}
}
