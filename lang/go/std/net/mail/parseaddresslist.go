package main

import (
	"fmt"
	"log"
	"net/mail"
)

func main() {
	const list = "Gitter <git@ctriple.cn>, Linux <l@ctriple.cn>, GitHub <g@ctriple.cn>, Chou <p@ctriple.cn>"
	emails, err := mail.ParseAddressList(list)
	if err != nil {
		log.Fatal(err)
	}
	for _, v := range emails {
		fmt.Println(v.Name, v.Address)
	}
}
