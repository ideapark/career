package main

import (
	"encoding/json"
	"encoding/xml"
	"fmt"
	"io"
	"log"
	"strings"
)

type Website struct {
	Name string
	Year int
	URL  string
}

var jsonLines = `
	{"Name": "Python", "Year": 1991, "URL": "http://python.org/"}
	{"Name": "Ruby", "Year": 1995, "URL": "http://www.ruby-lang.org/en/"}
	{"Name": "Scala", "Year": 2003, "URL": "http://www.scala-lang.org/"}
	{"Name": "Go", "Year": 2009, "URL": "http://golang.org/"}
`

func do(jsonLines string, f func(Website)) {
	dec := json.NewDecoder(strings.NewReader(jsonLines))
	for {
		var website Website
		err := dec.Decode(&website)
		if err != nil {
			if err == io.EOF {
				break
			}
			log.Fatal(err)
		}
		f(website)
	}
}

func main() {
	do(jsonLines, func(website Website) {
		fmt.Printf("%#v\n", website)
	})

	do(jsonLines, func(website Website) {
		xml, err := xml.MarshalIndent(website, "", "  ")
		if err != nil {
			log.Fatal(err)
		}
		fmt.Printf("%s\n", xml)
	})
}
