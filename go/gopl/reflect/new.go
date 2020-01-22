package main

import (
	"fmt"
	"reflect"
)

func main() {
	a := reflect.ArrayOf(10, reflect.TypeOf(byte(0)))
	m := reflect.MapOf(reflect.TypeOf(""), reflect.TypeOf(0))

	fmt.Println(a, m)
}
