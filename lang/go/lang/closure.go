package main

func closure(x int) func() {
	println(&x)
	return func() {
		println(&x, x)
	}
}

func main() {
	f := closure(256)
	f()
}

/*
// disable inline & opt
go build -gcflags "-N -l -m" closure.go
# command-line-arguments
./closure.go:5: func literal escapes to heap
./closure.go:5: func literal escapes to heap
./closure.go:6: &x escapes to heap
./closure.go:3: moved to heap: x
./closure.go:4: closure &x does not escape
./closure.go:6: closure.func1 &x does not escape
*/
