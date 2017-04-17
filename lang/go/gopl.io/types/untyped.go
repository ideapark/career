package main

import (
	"fmt"
)

func main() {
	var f float64 = 3 + 0i // untyped complex -> float64
	f = 2                  // untyped integer -> float64
	f = 1e123              // untyped floating-point -> float64
	f = 'a'                // untyped rune -> float64
	_ = f                  // compile error elimination

	fmt.Printf("%T\n", 0)      // "int"
	fmt.Printf("%T\n", 0.0)    // "float64"
	fmt.Printf("%T\n", 0i)     // "complex128"
	fmt.Printf("%T\n", '\000') // "int32" (rune)
}
