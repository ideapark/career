package main

import (
	"bytes"
	"encoding/base64"
	"io"
	"os"
)

func main() {
	// A buffer can turn a string or a []byte into an io.Reader.
	buf := bytes.NewBufferString("R29waGVycydWxlIQ==")
	dec := base64.NewDecoder(base64.StdEncoding, buf)
	io.Copy(os.Stdout, dec)
}
