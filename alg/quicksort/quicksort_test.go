// Copyright 2020 (C) Zhou Peng <p@thinpark.io>

package quicksort

import (
	"testing"
)

func TestInts(t *testing.T) {
	ints := []int{5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5}
	Ints(ints)
	for i := 0; i < len(ints)-1; i++ {
		if ints[i] > ints[i+1] {
			t.Fatalf("[%d, %d] not sorted.", ints[i], ints[i+1])
		}
	}
}

func TestFloat64(t *testing.T) {
	flts := []float64{5.0, 4.0, 3.0, 2.0, 1.0, 0.0, -1.0, -2.0, -3.0, -4.0, -5.0}
	Float64s(flts)
	for i := 0; i < len(flts)-1; i++ {
		if flts[i] > flts[i+1] {
			t.Fatalf("[%f, %f] not sorted.", flts[i], flts[i+1])
		}
	}
}

func TestStrings(t *testing.T) {
	strs := []string{"the", "quick", "brown", "fox", "jumped", "over", "the", "lazy", "dog"}
	Strings(strs)
	for i := 0; i < len(strs)-1; i++ {
		if strs[i] > strs[i+1] {
			t.Fatalf("[%s, %s] not sorted.", strs[i], strs[i+1])
		}
	}
}
