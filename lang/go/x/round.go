package main

// round n up to a multiple of a.
// a must be a power of 2.
func round(n, a uintptr) uintptr {
	return (n + a - 1) &^ (a - 1)
}

func main() {
	println(round(10, 8))
	println(round(3, 4))
	println(round(1, 2))
}
