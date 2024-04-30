// Copyright 2020 © Park Zhou <ideapark@petalmail.com>

package kmp

import (
	"fmt"
)

func Example() {
	text := "the quick brown fox jumped over the lazy dog"
	word := "the"
	match := Search(text, word)
	for i := 0; i < len(match); i++ {
		fmt.Println(match[i])
	}

	// Output:
	// 0
	// 32
}
