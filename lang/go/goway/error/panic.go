package main

import "fmt"

func main() {
	fmt.Println("Starting the program")
	panic("A severe error occurred: stopping the pgoram!")
	fmt.Println("Ending the program")
}
