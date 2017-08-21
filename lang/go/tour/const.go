// Why constant is not addressable in golang?
//
// I guess that const will be substitute literally at compile time
// for performance improvements. So there is not such variable in
// run time.

package main

import "fmt"
import "math"

const s string = "constant"

func main() {
	fmt.Println(s)

	const n = 500000000

	const d = 3e20 / n
	fmt.Println(d)

	fmt.Println(int64(d))

	fmt.Println(math.Sin(n))
}
