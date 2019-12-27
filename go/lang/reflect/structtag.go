package main

import (
	"fmt"
	"reflect"
)

type user struct {
	FirstName string `json:"first_name" xml:"first-name"`
	LastName  string `json:"last_name" xml:"last-name"`
}

func main() {
	u := user{}

	t := reflect.TypeOf(u)
	for i := 0; i < t.NumField(); i++ {
		f := t.Field(i)
		fmt.Printf("%s: %s %s\n", f.Name, f.Tag.Get("json"), f.Tag.Get("xml"))
	}
}
