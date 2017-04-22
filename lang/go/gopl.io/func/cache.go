// Outer struct automatically has inner struct's method
package cache

import (
	"sync"
)

type Cache struct {
	sync.Mutex
	mapping map[string]string
}

var cache = Cache{mapping: make(map[string]string)}

func Lookup(key string) (val string, ok bool) {
	cache.Lock()
	defer cache.Unlock()
	val, ok = cache.mapping[key]
	return
}
