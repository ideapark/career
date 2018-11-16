package main

import (
	"fmt"
)

func main() {
	for i := 0; i < 5; i++ {
		defer fmt.Println(i)
	}
	for i := 5; i < 10; i++ {
		defer fmt.Println(i)
	}
}
