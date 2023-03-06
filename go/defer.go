package main

// withoutdefer shows an error case not working as expected.
func withoutdefer() {
	defer func() {
		if err := recover(); err != nil {
			println(err.(string))
		}
	}()

	println("lock()")
	panic("lock leaking")
	println("unlock()")
}

// withdefer shows a correct case working against the panic.
func withdefer() {
	defer func() {
		if err := recover(); err != nil {
			println(err.(string))
		}
	}()

	println("lock()")
	defer println("unlock()")
	panic("lock released")
}

func main() {
	println("===> misbehaves without defer")
	withoutdefer()

	println("===> being well with defer")
	withdefer()
}
