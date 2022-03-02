// Copyright 2022 © Park Zhou <park@ideapark.io>

package huffman

import (
	"testing"
)

func TestEncodeDecode(t *testing.T) {
	inputs := []string{
		"",
		"Go",
		"general-purpose language",
		"strongly typed and garbage-collected",
		"concurrent programming",
		"packages",
	}
	for _, rawdata := range inputs {
		coding, encdata := Encode(rawdata)
		decdata := Decode(coding, encdata)

		if decdata != rawdata {
			t.Fatalf("\nrawdata: %s\n encdata: %s\n decdata: %s\n\n", rawdata, encdata, decdata)
		}
	}
}
