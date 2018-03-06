// Title treats s as UTF-8-encoded bytes and returns a copy with all Unicode
// letters that begin words mapped to their title case.
//
// BUG(rsc): The rule Title uses for word boundaries does not handle Unicode
// punctuation properly.
package main

import (
	"bytes"
	"fmt"
)

func main() {
	fmt.Printf("%s", bytes.Title([]byte("her royal highness")))
}
