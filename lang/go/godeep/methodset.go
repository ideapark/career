package main

import (
	"fmt"
	"reflect"
)

type S struct{}

type T struct {
	S
}

func (S) SVal()  {}
func (*S) SPtr() {}
func (T) TVal()  {}
func (*T) TPtr() {}

func methodSet(a interface{}) {
	t := reflect.TypeOf(a)

	for i, n := 0, t.NumMethod(); i < n; i++ {
		m := t.Method(i)
		fmt.Println(m.Name, m.Type)
	}
}

func main() {
	t := T{}

	methodSet(t)
	methodSet(&t)
}
