package main

import (
	"fmt"
)

func main() {
	data := [3]int{10, 20, 30}

	// range will copy data
	for i, x := range data {
		if i == 0 {
			data[0] += 100
			data[1] += 100
			data[2] += 100
		}
		fmt.Printf("x: %d, data: %d\n", x, data)
	}

	// range will copy slice
	for i, x := range data[:] {
		if i == 0 {
			data[0] += 100
			data[1] += 100
			data[2] += 100
		}
		fmt.Printf("x: %d, data: %d\n", x, data)
	}
}
