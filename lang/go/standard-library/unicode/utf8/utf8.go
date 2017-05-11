package main

import (
	"fmt"
	"unicode/utf8"
)

func main() {
	str := "Hello, 世界"
	for len(str) > 0 {
		r, size := utf8.DecodeLastRuneInString(str)
		fmt.Printf("%c %v\n", r, size)

		str = str[:len(str)-size]
	}

	b := []byte("Hello, 世界")
	for len(b) > 0 {
		r, size := utf8.DecodeRune(b)
		fmt.Printf("%c %v\n", r, size)

		b = b[size:]
	}

	r := '世'
	buf := make([]byte, 3)
	n := utf8.EncodeRune(buf, r)
	fmt.Println(buf)
	fmt.Println(n)

	valid := []byte("Hello, 世界")
	invalid := []byte{0xff, 0xfe, 0xfd}
	fmt.Println(utf8.Valid(valid))
	fmt.Println(utf8.Valid(invalid))
}
