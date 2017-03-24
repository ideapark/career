package main

import (
	"fmt"
	"io/ioutil"
	"os"
)

func main() {
	inputFile := "file_readwrite.go"
	outputFile := "/tmp/discard.txt"
	buf, err := ioutil.ReadFile(inputFile)
	if err != nil {
		fmt.Fprintf(os.Stderr, "File Error: %s\n", err)
	}
	fmt.Printf("%s\n", string(buf))
	err = ioutil.WriteFile(outputFile, buf, 0x644)
	if err != nil {
		panic(err.Error())
	}
}
