package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
)

func main() {
	res, err := http.Get("http://www.archlinux.org")
	if err != nil {
		log.Fatal(err)
	}
	defer res.Body.Close()

	archlinux, err := ioutil.ReadAll(res.Body)
	if err != nil {
		log.Fatal(err)
	}
	fmt.Printf("%s", archlinux)
}
