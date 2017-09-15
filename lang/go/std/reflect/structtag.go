// StructTag
//
//                 space separation
//                      |
//                      ^
// `json:"foo,omitempty" xml:"bar"`
//               ^
//               |
//           option (not part of the spec)

package main

import (
	"fmt"
	"reflect"
)

func main() {
	type S struct {
		F string `species:"gopher" color:"blue"`
	}
	s := S{}
	st := reflect.TypeOf(s)
	field := st.Field(0)
	fmt.Println(field.Tag.Get("color"), field.Tag.Get("species"))
}
