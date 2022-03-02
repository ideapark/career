// Copyright 2020 © Park Zhou <park@ideapark.io>

package kmp

import (
	"strings"
	"testing"
)

func TestSearch(t *testing.T) {
	text := "the quick brown fox jumped over the lazy dog"
	word := "the"

	want := []int{
		strings.Index(text, word),
		strings.LastIndex(text, word),
	}
	got := Search(text, word)

	if len(want) != len(got) {
		t.Fatal("missing")
	}
	for i := 0; i < len(want); i++ {
		if want[i] != got[i] {
			t.Fatalf("want:%d, got:%d\n", want[i], got[i])
		}
	}
}
