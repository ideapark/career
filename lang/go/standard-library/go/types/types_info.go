package main

import (
	"bytes"
	"fmt"
	"go/ast"
	"go/parser"
	"go/token"
	"go/types"
	"log"
	"sort"
	"strings"
)

func main() {
	// Parse a single source file.
	const input = `
package fib

type S string

var a, b, c = len(b), S(c), "hello"

func fib(x int) int {
        if x < 2 {
                return x
        }
        return fib(x-1) - fib(x-2)
}
`
	fset := token.NewFileSet()
	f, err := parser.ParseFile(fset, "fib.go", input, 0)
	if err != nil {
		log.Fatal(err)
	}

	// Type-check the package.
	// We create an empty map for each kind of input
	// We're interested in, and Check populates them.
	info := types.Info{
		Types: make(map[ast.Expr]types.TypeAndValue),
		Defs:  make(map[*ast.Ident]types.Object),
		Uses:  make(map[*ast.Ident]types.Object),
	}
	var conf types.Config
	pkg, err := conf.Check("fib", fset, []*ast.File{f}, &info)
	if err != nil {
		log.Fatal(err)
	}

	// Print package-level variables in initialization order.
	fmt.Printf("InitOrder: %v\n\n", info.InitOrder)

	// For each named object, print the line and
	// column of its definition and each of its uses.
	fmt.Println("Defs and Uses of each named object:")
	usesByObj := make(map[types.Object][]string)
	for id, obj := range info.Uses {
		posn := fset.Position(id.Pos())
		lineCol := fmt.Sprintf("%d:%d", posn.Line, posn.Column)
		usesByObj[obj] = append(usesByObj[obj], lineCol)
	}
	var items []string
	for obj, uses := range usesByObj {
		sort.Strings(uses)
		item := fmt.Sprintf("%s:\n defined at %s\n used at %s",
			types.ObjectString(obj, types.RelativeTo(pkg)),
			fset.Position(obj.Pos()),
			strings.Join(uses, ", "))
		items = append(items, item)
	}
	sort.Strings(items) // sort by line:col, in effect
	fmt.Println(strings.Join(items, "\n"))
	fmt.Println()

	fmt.Println("Types and Values of each expression:")
	items = nil
	for expr, tv := range info.Types {
		var buf bytes.Buffer
		posn := fset.Position(expr.Pos())
		tvstr := tv.Type.String()
		if tv.Value != nil {
			tvstr += " = " + tv.Value.String()
		}
		// line:col | expr | mode : type = value
		fmt.Fprintf(&buf, "%2d:%2d | %-19s | %-7s : %s",
			posn.Line, posn.Column, exprString(fset, expr),
			mode(tv), tvstr)
		items = append(items, buf.String())
	}
	sort.Strings(items)
	fmt.Println(strings.Join(items, "\n"))
}

func exprString(fset *token.FileSet, expr ast.Expr) string {
	return fset.Position(expr.Pos()).String()
}

func mode(tv types.TypeAndValue) string {
	var str string
	if tv.Type != nil {
		str += tv.Type.String()
	}
	if tv.Value != nil {
		str += ":"
		str += tv.Value.String()
	}
	return str
}
