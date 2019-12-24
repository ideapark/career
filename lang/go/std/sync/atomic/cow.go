package main

import (
	"fmt"
	"math/rand"
	"strconv"
	"sync"
	"sync/atomic"
	"time"
)

type Map map[string]string

var m atomic.Value
var mu sync.Mutex // used only by writers

func init() {
	m.Store(make(Map))
}

// read function can be used to read the data without further synchronization
var read = func(key string) (val string) {
	m1 := m.Load().(Map)
	return m1[key]
}

// write function can be used to update the data without further synchronization
var write = func(key, val string) {
	mu.Lock() // synchronize with other potential writers
	defer mu.Unlock()
	m1 := m.Load().(Map) // load current value of the data structure
	m2 := make(Map)      // create a new value
	for k, v := range m1 {
		m2[k] = v // copy all data from the current object to the new one
	}
	m2[key] = val // do the update that we need
	m.Store(m2)   // atomically replace the current object with the new one
	// At this point all new readers start working with the new version.
	// The old version will be garbage collected once the existing readers
	// (if any) are down with it.
}

func main() {
	done := make(chan struct{})
	// Reader
	go func() {
		rFreq := time.Tick(1 * time.Second)
		for {
			select {
			case <-done:
				break
			case <-rFreq:
				fmt.Println(read("hello"))
			}
		}
	}()
	// Writer
	go func() {
		wFreq := time.Tick(5 * time.Second)
		for {
			select {
			case <-done:
				break
			case <-wFreq:
				write("hello", strconv.Itoa(rand.Int()))
			}
		}
	}()
	time.Sleep(20 * time.Second)
	done <- struct{}{}
	done <- struct{}{}
}
