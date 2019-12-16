// Go has various value types including strings, integers, floats, booleans,
// etc. Here are a few basic examples.
//
// Strings, which can be added together with +.
// Integers and floats.
// Booleans, with boolean operators as you’d expect.

package main

import "fmt"

func main() {
	fmt.Println("go" + "lang")

	fmt.Println("1+1 =", 1+1)
	fmt.Println("7.0/3.0 =", 7.0/3.0)

	fmt.Println(true && false)
	fmt.Println(true || false)
	fmt.Println(!true)
}
