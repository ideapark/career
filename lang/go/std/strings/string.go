package main

import (
	"fmt"
	"strings"
	"unicode"
)

func main() {
	fmt.Println(strings.Contains("seafood", "foo"))
	fmt.Println(strings.ContainsAny("failure", "u & i"))
	fmt.Println(strings.Count("five", "")) // before & after each rune
	fmt.Println(strings.EqualFold("Go", "go"))
	fmt.Printf("Fields are: %q\n", strings.Fields("  foo bar  baz   "))

	f := func(c rune) bool {
		return !unicode.IsLetter(c) && !unicode.IsNumber(c)
	}
	fmt.Printf("Fields are: %q\n", strings.FieldsFunc("  foo1;bar2,baz3...", f))
	fmt.Println(strings.HasPrefix("Gopher", "Go"))
	fmt.Println(strings.HasSuffix("Amigo", "go"))
	fmt.Println(strings.Index("chicken", "ken"))
	fmt.Println(strings.IndexAny("chicken", "aeiouy"))

	h := func(c rune) bool {
		return unicode.Is(unicode.Han, c)
	}
	fmt.Println(strings.IndexFunc("Hello, 世界", h))
	fmt.Println(strings.IndexRune("chicken", 'k'))

	s := []string{"foo", "bar", "baz"}
	fmt.Println(strings.Join(s, ", "))
	fmt.Println(strings.Index("go gopher", "go"))

	rot13 := func(r rune) rune {
		switch {
		case r >= 'A' && r <= 'Z':
			return 'A' + (r-'A'+13)%26
		case r >= 'a' && r <= 'z':
			return 'a' + (r-'a'+13)%26
		}
		return r
	}
	fmt.Println(strings.Map(rot13, "'Twas brillig and the slithy gopher..."))
	fmt.Println("ba" + strings.Repeat("na", 2))
	fmt.Println(strings.Replace("oink oink oink", "k", "ky", 2))
	fmt.Printf("%q\n", strings.Split("a,b,c", ","))
	fmt.Printf("%q\n", strings.SplitAfter("a,b,c", ","))
	fmt.Printf("%q\n", strings.SplitAfterN("a,b,c", ",", 2))
	fmt.Printf("%q\n", strings.SplitN("a,b,c", ",", 2))
	fmt.Println(strings.Title("her royal highness"))
	fmt.Println(strings.ToLower("Gopher"))
	fmt.Println(strings.ToTitle("loud noises"))
	fmt.Println(strings.ToUpper("Gopher"))
	fmt.Printf("[%q]", strings.Trim("!!! Achtung! Achtung !!!", "! "))
	fmt.Println(strings.TrimPrefix("Goodbye,, World", "Goodbye,"))
	fmt.Println(strings.TrimSpace(" \t\n a lone gopher \n\t\r\n"))
	fmt.Println(strings.NewReplacer("<", "&lt;", ">", "&gt;").Replace("This is <b>HTML</b>!"))
}
