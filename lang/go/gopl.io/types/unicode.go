package main

import (
	"fmt"
	"unicode/utf8"
)

func main() {
	s := "Hello, 世界"
	fmt.Println("bytes: ", len(s))
	fmt.Println("runes: ", utf8.RuneCountInString(s))

	n := 0
	for range s {
		n++
	}
	fmt.Println("runes by range: ", n)

	for i := 0; i < len(s); {
		r, size := utf8.DecodeRuneInString(s[i:])
		fmt.Printf("%d\t%c\n", i, r)
		i += size
	}

	// range performs UTF-8 decoding implicitly
	for i, r := range s {
		fmt.Printf("%d\t%q\t%d\n", i, r, r)
	}
}
