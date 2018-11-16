package main

func wantInt() *int {
	i := 0x100
	return &i
}

func main() {
	a := wantInt()
	println(a, *a)
}
