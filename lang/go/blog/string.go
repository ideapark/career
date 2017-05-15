/*
https://golang.org/blog/strings

Go source code is always UTF-8.
A string holds arbitrary bytes.
A string literal, absent byte-level escapes, always holds valid UTF-8 sequences.
Those sequences represent Unicode code points, called runes.
No guarantee is made in Go that characters in strings are normalized.
*/

package main

import (
	"fmt"
)

func main() {
	// string holds arbitrary bytes, it is not required to hold
	// unicode text, utf-8 text, or any other predefined format.
	// as far as the content of a string is concerned, it is
	// exactly equivalent to a slice of bytes.
	const sample = "\xbd\xb2\x3d\xbc\x20\xe2\x8c\x98"

	// Produce mess
	fmt.Println(sample)

	// Loop string's bytes
	for i := 0; i < len(sample); i++ {
		fmt.Printf("%x ", sample[i])
	}
	fmt.Println()

	// Equivalent to upper (notice the space between % and x)
	fmt.Printf("% x\n", sample)

	// The %q (quoted) verb will escape any non-printable bytes
	fmt.Printf("%q\n", sample)

	// Also escape unicode value
	fmt.Printf("%+q\n", sample)

	const nihongo = "日本語"
	for index, runeValue := range nihongo {
		fmt.Printf("%#U starts at byte position %d\n", runeValue, index)
	}
}
