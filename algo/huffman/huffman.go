// Copyright 2022 © Park Zhou <ideapark@petalmail.com>

// Package huffman implements huffman coding algorithm
//
//  https://en.wikipedia.org/wiki/Huffman_coding
//
// In computer science and information theory, a Huffman code is a
// particular type of optimal prefix code that is commonly used for
// lossless data compression. The process of finding or using such a
// code proceeds by means of Huffman coding, an algorithm developed by
// David A. Huffman while he was a Sc.D. student at MIT, and published
// in the 1952 paper "A Method for the Construction of
// Minimum-Redundancy Codes".
//
// The output from Huffman's algorithm can be viewed as a
// variable-length code table for encoding a source symbol (such as a
// character in a file). The algorithm derives this table from the
// estimated probability or frequency of occurrence (weight) for each
// possible value of the source symbol. As in other entropy encoding
// methods, more common symbols are generally represented using fewer
// bits than less common symbols. Huffman's method can be efficiently
// implemented, finding a code in time linear to the number of input
// weights if these weights are sorted. However, although optimal
// among methods encoding symbols separately, Huffman coding is not
// always optimal among all compression methods - it is replaced with
// arithmetic coding or asymmetric numeral systems if better
// compression ratio is required.
//
package huffman

import (
	"bytes"
	"fmt"
	"os"
	"sort"
	"strings"
)

const (
	debug = false
)

type huffmanNode struct {
	left   *huffmanNode
	right  *huffmanNode
	symbol []rune // leaf node: len(symbol) == 1
	weight int
}

type byWeight []*huffmanNode

func (l byWeight) Len() int {
	return len(l)
}
func (l byWeight) Less(i, j int) bool {
	return l[i].weight < l[j].weight
}
func (l byWeight) Swap(i, j int) {
	l[i], l[j] = l[j], l[i]
}

// Encode encode a raw string with huffman coding. It will return the
// encoded string and the huffman coding table together.
func Encode(rawdata string) (coding map[rune]string, encdata string) {
	// symbol weight table
	weight := make(map[rune]int)
	for _, r := range rawdata {
		w := weight[r]
		weight[r] = w + 1
	}

	var nodelist []*huffmanNode

	for r, w := range weight {
		n := &huffmanNode{
			left:   nil,
			right:  nil,
			symbol: []rune{r},
			weight: w,
		}
		nodelist = append(nodelist, n)
	}

	sort.Stable(byWeight(nodelist))

	// empty rawdata?
	if len(nodelist) == 0 {
		return nil, ""
	}

	// keep merging the first 2 smallest weight huffman node until
	// there is only one huffman node
	for len(nodelist) > 1 {
		n1, n2 := nodelist[0], nodelist[1]

		symbol := []rune{}
		symbol = append(symbol, n1.symbol...)
		symbol = append(symbol, n2.symbol...)

		n := &huffmanNode{
			left:   n1,
			right:  n2,
			symbol: symbol,
			weight: n1.weight + n2.weight,
		}

		// drop the two merged, add the new one
		nodelist = nodelist[2:]
		nodelist = append(nodelist, n)

		sort.Stable(byWeight(nodelist))
	}

	huffmanRoot := nodelist[0]

	printTree(huffmanRoot, 0)

	coding = make(map[rune]string)

	code(coding, huffmanRoot, "1")

	var buf bytes.Buffer
	for _, r := range rawdata {
		buf.WriteString(coding[r])
	}

	return coding, buf.String()
}

// code traverse the huffman coding tree, when encounter a leaf node,
// it records the symbol coding.
func code(coding map[rune]string, node *huffmanNode, prefix string) {
	// reach a leaf huffman node
	if len(node.symbol) == 1 {
		coding[node.symbol[0]] = prefix
		return
	}

	// turn left with "1"
	if node.left != nil {
		code(coding, node.left, prefix+"1")
	}
	// turn right with "0"
	if node.right != nil {
		code(coding, node.right, prefix+"0")
	}
}

// Decode decode a huffman coding encoded string to the raw
// string. Note that it also require the coding table returned with
// the encoded string from Encode to work correctly.
func Decode(coding map[rune]string, encdata string) (rawdata string) {
	huffmanRoot := &huffmanNode{
		left:   nil,
		right:  nil,
		symbol: []rune{},
		weight: 0,
	}

	for r, code := range coding {
		if len(code) < 1 || code[0] != '1' {
			panic("bad coding")
		}
		tree(huffmanRoot, r, code[1:])
	}

	printTree(huffmanRoot, 0)

	var (
		buf      bytes.Buffer
		decNode  *huffmanNode
		decStart bool = true
	)
	for _, bit := range encdata {
		if decStart {
			decStart = false
			decNode = huffmanRoot

			// special case: there is only one root huffman node
			if len(decNode.symbol) == 1 {
				buf.WriteRune(decNode.symbol[0])
				decStart = true
			}

			continue
		}

		switch bit {
		case '1':
			decNode = decNode.left
		case '0':
			decNode = decNode.right
		default:
			panic("bad encdata")
		}

		// reach a leaf huffman node
		if len(decNode.symbol) == 1 {
			buf.WriteRune(decNode.symbol[0])
			decStart = true
		}
	}

	return buf.String()
}

// tree rebuild the huffman coding tree
func tree(node *huffmanNode, r rune, code string) {
	node.symbol = append(node.symbol, r)

	if len(code) == 0 {
		return
	}

	switch bit := code[0]; bit {
	case '1':
		if node.left == nil {
			node.left = &huffmanNode{
				left:   nil,
				right:  nil,
				symbol: []rune{},
				weight: 0,
			}
		}
		tree(node.left, r, code[1:])
	case '0':
		if node.right == nil {
			node.right = &huffmanNode{
				left:   nil,
				right:  nil,
				symbol: []rune{},
				weight: 0,
			}
		}
		tree(node.right, r, code[1:])
	default:
		panic("bad code")
	}
}

// debug
func printTree(node *huffmanNode, ident int) {
	if !debug {
		return
	}

	if node == nil {
		return
	}

	join := func(symbol []rune) string {
		var buf bytes.Buffer
		buf.WriteString("(")
		for i, r := range symbol {
			buf.WriteRune(r)
			if i < len(symbol)-1 {
				buf.WriteRune(',')
			}
		}
		buf.WriteString(")")
		return buf.String()
	}

	fmt.Fprintf(os.Stderr, "%s(%s:%d)\n", strings.Repeat("...", ident), join(node.symbol), node.weight)

	if node.left != nil {
		printTree(node.left, ident+1)
	}

	if node.right != nil {
		printTree(node.right, ident+1)
	}
}
