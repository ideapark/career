---
title: Stack Traces In Go
author: William Kennedy
email: bill@ardanlabs.com
---

# Goroutine must panic

```go
  package main

  type T int

  func main() {
    var t T = T(0)
    slice := make([]string, 2, 4)
    t.mustpanic(slice, "panic", 10, true, true, false)
  }

  func (t *T) mustpanic(slice []string, str string, i int, b1, b2, b3 bool) {
    println(t)
    panic("Want stack trace")
  }
```

# Stack trace

```bash
  0xc420039f30
  panic: Want stack trace

  goroutine 1 [running]:
  main.(*T).mustpanic(0xc420039f30, 0xc420039f38, 0x2, 0x4, 0x46919c, 0x5, 0xa, 0x101)
    /tmp/t.go:13 +0x81
  main.main()
    /tmp/t.go:8 +0xa7
  exit status 2
```

# Explains

- Method is just special function with first argument specified
- Slice and String arguments are be splited by their internal representation
  Slice{data,len,cap}, String{data,len}.
- Bool, int arguments may be wrapped togther for performance speed up
