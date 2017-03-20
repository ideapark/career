package main

import "fmt"

func main() {
	var arrAge = [5]int{18, 20, 15, 22, 16}
	for i := 0; i < len(arrAge); i++ {
		fmt.Printf("%d\n", arrAge[i])
	}

	// array length calculated by go compiler
	var arrLazy = [...]int{5, 6, 7, 8, 22}
	for i := 0; i < len(arrLazy); i++ {
		fmt.Printf("%d\n", arrLazy[i])
	}

	// <key: value> initialization format
	var arrKeyValue = [5]string{3: "Chris", 4: "Ron"}
	for i := 0; i < len(arrKeyValue); i++ {
		fmt.Printf("Person at %d is %s\n", i, arrKeyValue[i])
	}

	// pointer array
	for i := 0; i < 3; i++ {
		fp(&[3]int{i, i * i, i * i * i})
	}
}

func fp(a *[3]int) {
	fmt.Println(a)
}
