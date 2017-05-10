package main

import (
	"fmt"
	"strconv"
)

func mian() {
	b := []byte("bool:")
	b = strconv.AppendBool(b, true)
	fmt.Println(string(b))

	b32 := []byte("float32:")
	b32 = strconv.AppendFloat(b32, 3.1415926535, 'E', -1, 32)
	fmt.Println(string(b32))

	b10 := []byte("int (base 10):")
	b10 = strconv.AppendInt(b10, -42, 10)
	fmt.Println(string(b10))

	bq := []byte("quote:")
	bq = strconv.AppendQuote(bq, `"Fran & Freddie's Diner"`)
	fmt.Println(string(bq))
}
