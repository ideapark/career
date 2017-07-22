package main

import (
	"fmt"
	"log"
	"net/mail"
)

func main() {
	e, err := mail.ParseAddress("Docker <d@ctriple.cn>")
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println(e.Name, e.Address)
}
