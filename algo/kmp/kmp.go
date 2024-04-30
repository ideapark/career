// Copyright 2020 © Park Zhou <ideapark@petalmail.com>

// Package implements Knuth–Morris–Pratt algorithm.
// https://en.wikipedia.org/wiki/Knuth-Morris-Pratt_algorithm
package kmp

// Search returns a slice of offsets in text which start a matching with word.
func Search(text string, word string) []int {
	return kmp(text, word)
}

func table(word string) (table []int) {
	table = make([]int, len(word))
	// 1st, 2nd are constants when len(word)<=2
	copy(table, []int{-1, 0})
	for pos, cnd := 2, 0; pos+cnd < len(word); {
		if word[pos-1] == word[cnd] {
			cnd++
			table[pos] = cnd
			pos++
		} else if cnd > 0 {
			cnd = table[cnd]
		} else {
			table[pos] = 0
			pos++
		}
	}
	return
}

func kmp(text string, word string) (match []int) {
	t := table(word)
	for m, i := 0, 0; m+i < len(text); {
		if word[i] == text[m+i] {
			// found match
			if i == len(word)-1 {
				match = append(match, m)
				m++
			} else {
				i++
			}
		} else {
			if t[i] > -1 {
				m = m + i - t[i]
				i = t[i]
			} else {
				m++
				i = 0
			}
		}
	}
	return
}
