package main

func bad(p *int) {
	go func() { // extends p's lifecycle
		println(p)
	}()
}

func main() {
	x := 100
	p := &x
	bad(p)
}

/*
go build -gcflags "-m" badptr.go
# command-line-arguments
./badptr.go:4: can inline bad.func1
./badptr.go:4: func literal escapes to heap
./badptr.go:4: func literal escapes to heap
./badptr.go:3: leaking param: p
./badptr.go:11: &x escapes to heap
./badptr.go:10: moved to heap: x
*/
