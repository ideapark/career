package main

import (
	"bytes"
	"fmt"
)

func main() {
	rot13 := func(r rune) rune {
		switch {
		case r >= 'A' && r <= 'z':
			return 'A' + (r-'A'+13)%26
		case r >= 'a' && r <= 'z':
			return 'a' + (r-'a'+13)%26
		}
		return r
	}
	fmt.Printf("%s", bytes.Map(rot13, []byte("Twas brilling and the slithy gopher...")))
}
