---
title: Golang GC Algorithm Phases
author: Rick Hudson
url: https://talks.golang.org/2015/go-gc.pdf
---

```text
+--------------------------------------------------------------------------------------------------+
|                          |   |                                                                   |
|       Off                |   | GC disabled                                                       |
|                          |   | Pointer values are just memory writes: *slot = ptr                |
+--------------------------|---|-------------------------------------------------------------------+
|                    |     |STW|                                                                   |
|     Stack Scan     |     |---+ Collect pointers from globals and goroutine stacks                |
|                    |     |   | Stacks scanned at preemption points                               |
+--------------------|     |   |-------------------------------------------------------------------+
|                    |     |   |                                                                   |
|       Mark         |WB on|   | Mark objects and follow pointers until pointer queue is empty     |
|                    |     |   | Write barrier tracks pointer changes by mutator                   |
+--------------------|     |---|-------------------------------------------------------------------+
|                    |     |   |                                                                   |
|  Mark termination  |     |STW| Rescan globals/changed stacks, finish marking, shrink stacks, ... |
|                    |     |   | Literature contains non-STW algorithms: keeping it simple for now |
+--------------------------|---|-------------------------------------------------------------------+
|                          |   |                                                                   |
|      Sweep               |   | Reclaim unmarked objects as needed                                |
|                          |   | Adjust GC pacing for next cycle                                   |
+--------------------------|   |-------------------------------------------------------------------+
|                          |   |                                                                   |
|       Off                |   | Rinse and repeat                                                  |
|                          |   |                                                                   |
+--------------------------------------------------------------------------------------------------+
```
WB: write barrier; STW: stop the world

# Getting to Go: The Journey of Go's Garbage Collector

## GC's view of Go

- Go is value-oriented

```go
type Reader struct { // archive/tar
    r    io.Reader
    curr numBytesReader
    skip int64
    blk  block
    err  error
}
type block [64]byte
```

```text
0        8        16       24       32
+-----------------------------------+
|r................|curr.............|
+-----------------------------------+
|skip....|blk.......................|
+-----------------------------------+
|...................................|
+-----------------------------------+
|........|err.............|         |
+-----------------------------------+
```

- Go allows interior pointers

```go
type Reader struct { // archive/tar
    r    io.Reader
    curr numBytesReader
    skip int64
    blk  block
    err  error
}
type block [64]byte

b = &r.blk
```

```text
0        8        16       24       32
+-----------------------------------+
|r................|curr.............|
+-----------------------------------+
|skip....|<---&r.blk................|
+-----------------------------------+
|...................................|
+-----------------------------------+
|........|err.............|         |
+-----------------------------------+
```

- Static ahead of time compilation

Binary contains entire runtime, No JIT recompilation.

- The two GC knobs

SetGCPercent
SetMaxHeap (not yet released but used and evaluated internally)
