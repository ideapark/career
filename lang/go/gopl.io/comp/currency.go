package main

import (
	"fmt"
)

type Currency int

const (
	USD Currency = iota
	EUR
	GBP
	RMB
)

func main() {
	symbol := [...]string{USD: "$", EUR: "#", GBP: "@", RMB: "&"}
	fmt.Println(RMB, symbol[RMB])
}
