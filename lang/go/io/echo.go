package main

import (
	"flag" // command line option parser
	"os"
)

// echo -n flag, of type *bool
var NewLine = flag.Bool("n", false, "print on newline")

const (
	Space   = " "
	Newline = "\n"
)

func main() {
	flag.PrintDefaults()
	flag.Parse()
	var s string = ""
	for i := 0; i < flag.NArg(); i++ {
		if i > 0 {
			s += Space
		}
		s += flag.Arg(i)
	}

	if *NewLine { // -n is parsed, flag becomes true
		s += Newline
	}
	os.Stdout.WriteString(s)
}
