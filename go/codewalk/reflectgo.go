package main

import (
	"os"
	"reflect"
	"strconv"
)

func main() {
	myPrint("Hello ", 42, "\n")
}

func myPrint(args ...interface{}) {
	for _, arg := range args {
		v := reflect.ValueOf(arg)
		switch v.Kind() {
		case reflect.String:
			os.Stdout.WriteString(v.String())
		case reflect.Int:
			os.Stdout.WriteString(strconv.FormatInt(v.Int(), 10))
			// other cases not included here yet
		}
	}
}
