package main

import (
	"reflect"
	"testing"
)

type Data struct {
	X int
}

var d = new(Data)

func set(x int) {
	d.X = x
}

func (x *Data) Inc() {
	x.X++
}

func rset(x int) {
	// cache v,f may improve some performance
	v := reflect.ValueOf(d).Elem()
	f := v.FieldByName("X")

	f.Set(reflect.ValueOf(x))
}

func call() {
	d.Inc()
}

func rcall() {
	var v = reflect.ValueOf(d)
	var m = v.MethodByName("Inc")
	m.Call(nil)
}

// Data modify benchmark
func BenchmarkSet(b *testing.B) {
	for i := 0; i < b.N; i++ {
		set(100)
	}
}

func BenchmarkRset(b *testing.B) {
	for i := 0; i < b.N; i++ {
		rset(100)
	}
}

// Method call benchmark
func BenchmarkCall(b *testing.B) {
	for i := 0; i < b.N; i++ {
		call()
	}
}

func BenchmarkRcall(b *testing.B) {
	for i := 0; i < b.N; i++ {
		rcall()
	}
}
