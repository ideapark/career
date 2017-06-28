package main

func main() {
	switch x := 5; x {
	default: // default must be executed AFTER the last case stmt
		x += 10
		println(x)
	case 5:
		x += 50
		println(x)
		fallthrough // execute next case stmt, need not match case condition
	case 6:
		x += 45
		println(x)
	}
}
