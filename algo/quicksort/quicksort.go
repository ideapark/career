// Copyright 2020 (C) Zhou Peng <p@iobuf.io>

// Package quicksort implements quick sorting algorithm. This is just a practice
// implemention, you should always use Go standard package sort instead.
//
// PROCEDURE quicksort(S):
//   IF S contains at most one element then
//     RETURN S
//   ELSE
//     BEGIN
//       choose an element V randomly from S;
//       let S1, S2 and S3 be the sequences of elements in S <, =, and > V, respectively;
//       RETURN (quicksort(S1) followed by S2 followed by quicksort(S3))
//     END
package quicksort

import (
	"math/rand"
	"sort"
)

type Interface interface {
	sort.Interface
}

// Sort sorts data using quick sorting algorithm
func Sort(data Interface) {
	quicksort(data, 0, data.Len())
}

func quicksort(data Interface, low, high int) {
	// nothing to do
	if high <= low {
		return
	}
	// move a random pivot element to data[low]
	pivot := low + rand.Intn(high-low)
	data.Swap(low, pivot)
	last := low
	for i := low; i < high; i++ {
		if data.Less(i, low) {
			last++
			data.Swap(i, last)
		}
	}
	// restore pivot
	data.Swap(low, last)
	// recursively sort each part
	quicksort(data, low, last)
	quicksort(data, last+1, high)
}

// --- Shortcuts for Go basic types ---

// intSlice attaches the methods of Interface to []int, sorting by ascending.
type intSlice []int

func (p intSlice) Len() int           { return len(p) }
func (p intSlice) Less(i, j int) bool { return p[i] < p[j] }
func (p intSlice) Swap(i, j int)      { p[i], p[j] = p[j], p[i] }

func Ints(data []int) {
	Sort(intSlice(data))
}

// float64Slice attaches the methods of Interface to []float64, sorting by ascending.
type float64Slice []float64

func (p float64Slice) Len() int           { return len(p) }
func (p float64Slice) Less(i, j int) bool { return p[i] < p[j] || isNaN(p[i]) && !isNaN(p[j]) }
func (p float64Slice) Swap(i, j int)      { p[i], p[j] = p[j], p[i] }
func isNaN(f float64) bool                { return f != f }

func Float64s(data []float64) {
	Sort(float64Slice(data))
}

// stringSlice attaches the methods of Interface to []string, sorting by ascending.
type stringSlice []string

func (p stringSlice) Len() int           { return len(p) }
func (p stringSlice) Less(i, j int) bool { return p[i] < p[j] }
func (p stringSlice) Swap(i, j int)      { p[i], p[j] = p[j], p[i] }

func Strings(data []string) {
	Sort(stringSlice(data))
}
