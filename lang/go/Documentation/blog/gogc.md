# Getting to Go: The Journey of Go's Garbage Collector

Richard L. Hudson

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
