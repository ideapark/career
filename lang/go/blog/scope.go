package main

import "fmt"

func main() {
	x := 100
	for i := 0; i < 5; i++ {
		x := i // NOTE: inner 'x' overrides outer 'x'
		fmt.Println(x)
	}
	fmt.Println(x)
}
