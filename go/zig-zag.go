package main

import "fmt"

func encode(v int32) uint32 {
	return uint32(v<<1) ^ uint32(v>>31)
}

func decode(u uint32) int32 {
	return int32(u>>1) ^ int32(u<<31)>>31
}

func main() {
	for i := int32(-10); i <= 10; i++ {
		fmt.Printf("%4d %4d %4d\n", i, encode(i), decode(encode(i)))
	}
}
