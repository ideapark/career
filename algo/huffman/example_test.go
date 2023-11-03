// Copyright 2022 © Park Zhou <ideapark@139.com>

package huffman

import (
	"fmt"
)

func ExampleEncode() {
	cases := []struct {
		input string
		want  []string // huffman coding varies
	}{
		{input: "", want: []string{""}},
		{input: "G", want: []string{"1"}},
		{input: "Go", want: []string{"1110", "1011"}},
	}
	for _, c := range cases {
		_, encdata := Encode(c.input)
		found := false
		for _, want := range c.want {
			if want == encdata {
				found = true
				break
			}
		}
		fmt.Println(found)
	}

	// Output:
	// true
	// true
	// true
}

func ExampleDecode() {
	cases := []struct {
		input  string
		coding map[rune]string
	}{
		{input: "1", coding: nil},
		{input: "1", coding: map[rune]string{'G': "1"}},
		{input: "1110", coding: map[rune]string{'G': "11", 'o': "10"}},
	}
	for _, c := range cases {
		rawdata := Decode(c.coding, c.input)
		fmt.Println(rawdata)
	}

	// Output:
	// G
	// Go
}
