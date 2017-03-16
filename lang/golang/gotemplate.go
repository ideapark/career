// Go Template
//
// (1) After import: declare constants, variables and the types
//
// (2) Then comes the init() function if there is any: this is a
// special function that every package can contain and that is
// executed first.
//
// (3) Then comes the main() function (only in the package main)
//
// (4) Then come the rest of the functions, the methods on the types
// first; or the functions in order as they are called from main()
// onwards; or the methods and functions alphabetically if the
// number of functions is high.
//
// Go Start
//
// (1) all packages in package main are imported in the order as
// indicated, in every package:
//
// (2) if it imports packages, (1) is called for this package
// (recursively) but a certain package is imported only once
//
// (3) the for every package (in reverse order) all constants and
// variables are evaluated, and the init() if it contains this
// function.
package main

import (
	"fmt"
)

const c = "C"

var v int = 5

type T struct{}

func init() {
	// initialization of package
}

func main() {
	var a int
	Func1()
	// ...
	fmt.Println(a)
}

func (t T) Method1() {
	// ...
}

func Func1() { // exported function Func1
	// ...
}
