package main

import (
	"fmt"
	"log"
	"os"
)

func main() {
	for i := 0; i < 10000; i++ {
		path := fmt.Sprintf("%d.log", i)
		f, err := os.Open(path)
		if err != nil {
			log.Println(err)
			continue
		}

		// BUG: two many open files, all files closed
		// until main func has ended.
		defer f.Close()

		// ... do something ...
	}
}
