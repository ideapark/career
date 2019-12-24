---
title: new() vs make()
author: Zhou Peng
email: p@ctriple.cn
---

* Difference between new() and make()

- new(T) allocates zeroed storage for a new item of type T and returns its
  address, a value of type *T: it =returns a pointer= to a newly allocated zero
  value of type T, ready for use; it applies to value types like arrays and
  structs; it is equivalent to &T{}

- make(T) =returns an initialized value= of type T; it applies only to the 3
  built-in reference types: slices, maps and channels.

In other words, new allocates; make initializes; the following illustrates this
difference:

```text
  new([]int)
    +------+
    |  *   | *[]int
    +---\--+
         \
	  +-----+-----+-----+
	  | nil |  0  |  0  | []int
	  +-----+-----+-----+
	   ptr   len   cap
```

```go
var p *[]int = new([]int)  // *p == nil; with len and cap 0
p := new([]int)
#+END_SRC

#+BEGIN_SRC text
  make([]int, 0)
    +-----+-----+-----+
    |  *  |  0  |  0  | []int
    +---\-+-----+-----+
     ptr \ len   cap
          \
	  ||[0]int
```

```go
p := make([]int, 0)  // slice is initialized, but here points to an empty array
```
