package main

func main() {
	x, y := 1, 2

	defer func(a int) {
		println("defer x, y = ", a, y) // y referenced by closure
	}(x) // x is copied and occured right here

	x += 100 // modified x not propagate to defer
	y += 200

	println(x, y)
}
