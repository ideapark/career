package main

import (
	"encoding/json"
	"fmt"
)

type Lang struct {
	Name string
	Year int
}

func main() {
	langs := []Lang{
		Lang{"C", 1970},
		Lang{"Java", 1995},
		Lang{"Python", 1991},
		Lang{"Go", 2009},
	}
	if data, err := json.MarshalIndent(langs, "", "  "); err == nil {
		fmt.Println(string(data))
	}
}
