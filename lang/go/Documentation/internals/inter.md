# Interface

## Golang call types

```text
| Known at compile time                       | Known at run time                      |
|---------------------------------------------|----------------------------------------|
| direct call of top-level func               |                                        |
| direct call of method with value receiver   |                                        |
| direct call of method with pointer receiver |                                        |
| indirect call of method on interface        | containing value with value method     |
| indirect call of method on interface        | containing pointer with value method   |
| indirect call of method on interface        | containing pointer with pointer method |
| indirect call of func value                 | set to top-level func                  |
| indirect call of func value                 | set to value method                    |
| indirect call of func value                 | set to pointer method                  |
| indirect call of func value                 | set to func literal                    |
```

## Example

```go
package main

//go:noinline
func Add(a, b int32) int32 {
	return a + b
}

type Adder struct {
	id int32
}

//go:noinline
func (adder *Adder) AddPtr(a, b int32) int32 {
	return a + b
}

//go:noinline
func (adder Adder) AddVal(a, b int32) int32 {
	return a + b
}

func main() {
	Add(10, 32) // direct call of top-level function

	adder := Adder{id: 6754}

	adder.AddPtr(10, 32)    // direct call of method with pointer receiver
	adder.AddVal(10, 32)    // direct call of method with value receiver
	(&adder).AddVal(10, 32) // implicit dereferencing
}
```

```shell
GOOS=linux GOARCH=amd64 go tool compile -S t.go
```

```asm
"".Add STEXT nosplit size=15 args=0x10 locals=0x0
	0x0000 00000 (f.go:4)	TEXT	"".Add(SB), NOSPLIT, $0-16
	0x0000 00000 (f.go:4)	FUNCDATA	$0, gclocals·f207267fbf96a0178e8758c6e3e0ce28(SB)
	0x0000 00000 (f.go:4)	FUNCDATA	$1, gclocals·33cdeccccebe80329f1fdbee7f5874cb(SB)
	0x0000 00000 (f.go:4)	MOVL	"".b+12(SP), AX
	0x0004 00004 (f.go:4)	MOVL	"".a+8(SP), CX
	0x0008 00008 (f.go:5)	ADDL	CX, AX
	0x000a 00010 (f.go:5)	MOVL	AX, "".~r2+16(SP)
	0x000e 00014 (f.go:5)	RET
	0x0000 8b 44 24 0c 8b 4c 24 08 01 c8 89 44 24 10 c3     .D$..L$....D$..
"".(*Adder).AddPtr STEXT nosplit size=15 args=0x18 locals=0x0
	0x0000 00000 (f.go:13)	TEXT	"".(*Adder).AddPtr(SB), NOSPLIT, $0-24
	0x0000 00000 (f.go:13)	FUNCDATA	$0, gclocals·54241e171da8af6ae173d69da0236748(SB)
	0x0000 00000 (f.go:13)	FUNCDATA	$1, gclocals·33cdeccccebe80329f1fdbee7f5874cb(SB)
	0x0000 00000 (f.go:13)	MOVL	"".b+20(SP), AX
	0x0004 00004 (f.go:13)	MOVL	"".a+16(SP), CX
	0x0008 00008 (f.go:14)	ADDL	CX, AX
	0x000a 00010 (f.go:14)	MOVL	AX, "".~r2+24(SP)
	0x000e 00014 (f.go:14)	RET
	0x0000 8b 44 24 14 8b 4c 24 10 01 c8 89 44 24 18 c3     .D$..L$....D$..
"".Adder.AddVal STEXT nosplit size=15 args=0x18 locals=0x0
	0x0000 00000 (f.go:18)	TEXT	"".Adder.AddVal(SB), NOSPLIT, $0-24
	0x0000 00000 (f.go:18)	FUNCDATA	$0, gclocals·54241e171da8af6ae173d69da0236748(SB)
	0x0000 00000 (f.go:18)	FUNCDATA	$1, gclocals·33cdeccccebe80329f1fdbee7f5874cb(SB)
	0x0000 00000 (f.go:18)	MOVL	"".b+16(SP), AX
	0x0004 00004 (f.go:18)	MOVL	"".a+12(SP), CX
	0x0008 00008 (f.go:19)	ADDL	CX, AX
	0x000a 00010 (f.go:19)	MOVL	AX, "".~r2+24(SP)
	0x000e 00014 (f.go:19)	RET
	0x0000 8b 44 24 10 8b 4c 24 0c 01 c8 89 44 24 18 c3     .D$..L$....D$..
"".main STEXT size=163 args=0x0 locals=0x28
	0x0000 00000 (f.go:22)	TEXT	"".main(SB), $40-0
	0x0000 00000 (f.go:22)	MOVQ	(TLS), CX
	0x0009 00009 (f.go:22)	CMPQ	SP, 16(CX)
	0x000d 00013 (f.go:22)	JLS	153
	0x0013 00019 (f.go:22)	SUBQ	$40, SP
	0x0017 00023 (f.go:22)	MOVQ	BP, 32(SP)
	0x001c 00028 (f.go:22)	LEAQ	32(SP), BP
	0x0021 00033 (f.go:22)	FUNCDATA	$0, gclocals·33cdeccccebe80329f1fdbee7f5874cb(SB)
	0x0021 00033 (f.go:22)	FUNCDATA	$1, gclocals·33cdeccccebe80329f1fdbee7f5874cb(SB)
	0x0021 00033 (f.go:23)	MOVQ	$137438953482, AX
	0x002b 00043 (f.go:23)	MOVQ	AX, (SP)
	0x002f 00047 (f.go:23)	PCDATA	$0, $0
	0x002f 00047 (f.go:23)	CALL	"".Add(SB)                                                   # direct call of top-level function
	0x0034 00052 (f.go:25)	MOVL	$6754, "".adder+28(SP)
	0x003c 00060 (f.go:27)	LEAQ	"".adder+28(SP), AX
	0x0041 00065 (f.go:27)	MOVQ	AX, (SP)
	0x0045 00069 (f.go:27)	MOVQ	$137438953482, AX
	0x004f 00079 (f.go:27)	MOVQ	AX, 8(SP)
	0x0054 00084 (f.go:27)	PCDATA	$0, $0
	0x0054 00084 (f.go:27)	CALL	"".(*Adder).AddPtr(SB)                                       # direct call of method with pointer receiver
	0x0059 00089 (f.go:28)	MOVL	"".adder+28(SP), AX
	0x005d 00093 (f.go:28)	MOVL	AX, (SP)
	0x0060 00096 (f.go:28)	MOVQ	$137438953482, AX
	0x006a 00106 (f.go:28)	MOVQ	AX, 4(SP)
	0x006f 00111 (f.go:28)	PCDATA	$0, $0
	0x006f 00111 (f.go:28)	CALL	"".Adder.AddVal(SB)                                          # direct call of method with value receiver
	0x0074 00116 (f.go:29)	MOVL	"".adder+28(SP), AX
	0x0078 00120 (f.go:29)	MOVL	AX, (SP)
	0x007b 00123 (f.go:29)	MOVQ	$137438953482, AX
	0x0085 00133 (f.go:29)	MOVQ	AX, 4(SP)
	0x008a 00138 (f.go:29)	PCDATA	$0, $0
	0x008a 00138 (f.go:29)	CALL	"".Adder.AddVal(SB)                                          # implicit dereferencing: receiver on the stack
	0x008f 00143 (f.go:30)	MOVQ	32(SP), BP
	0x0094 00148 (f.go:30)	ADDQ	$40, SP
	0x0098 00152 (f.go:30)	RET
	0x0099 00153 (f.go:30)	NOP
	0x0099 00153 (f.go:22)	PCDATA	$0, $-1
	0x0099 00153 (f.go:22)	CALL	runtime.morestack_noctxt(SB)
	0x009e 00158 (f.go:22)	JMP	0
	0x0000 64 48 8b 0c 25 00 00 00 00 48 3b 61 10 0f 86 86  dH..%....H;a....
	0x0010 00 00 00 48 83 ec 28 48 89 6c 24 20 48 8d 6c 24  ...H..(H.l$ H.l$
	0x0020 20 48 b8 0a 00 00 00 20 00 00 00 48 89 04 24 e8   H..... ...H..$.
	0x0030 00 00 00 00 c7 44 24 1c 62 1a 00 00 48 8d 44 24  .....D$.b...H.D$
	0x0040 1c 48 89 04 24 48 b8 0a 00 00 00 20 00 00 00 48  .H..$H..... ...H
	0x0050 89 44 24 08 e8 00 00 00 00 8b 44 24 1c 89 04 24  .D$.......D$...$
	0x0060 48 b8 0a 00 00 00 20 00 00 00 48 89 44 24 04 e8  H..... ...H.D$..
	0x0070 00 00 00 00 8b 44 24 1c 89 04 24 48 b8 0a 00 00  .....D$...$H....
	0x0080 00 20 00 00 00 48 89 44 24 04 e8 00 00 00 00 48  . ...H.D$......H
	0x0090 8b 6c 24 20 48 83 c4 28 c3 e8 00 00 00 00 e9 5d  .l$ H..(.......]
	0x00a0 ff ff ff                                         ...
	rel 5+4 t=16 TLS+0
	rel 48+4 t=8 "".Add+0
	rel 85+4 t=8 "".(*Adder).AddPtr+0
	rel 112+4 t=8 "".Adder.AddVal+0
	rel 139+4 t=8 "".Adder.AddVal+0
	rel 154+4 t=8 runtime.morestack_noctxt+0
"".(*Adder).AddVal STEXT dupok size=121 args=0x18 locals=0x20
	0x0000 00000 (<autogenerated>:1)	TEXT	"".(*Adder).AddVal(SB), DUPOK|WRAPPER, $32-24   # implicit dereferencing: receiver on the heap
	0x0000 00000 (<autogenerated>:1)	MOVQ	(TLS), CX                                       # WRAPPER: do not appear in backtraces and recover from panics thrown by the wrappee
	0x0009 00009 (<autogenerated>:1)	CMPQ	SP, 16(CX)
	0x000d 00013 (<autogenerated>:1)	JLS	99
	0x000f 00015 (<autogenerated>:1)	SUBQ	$32, SP
	0x0013 00019 (<autogenerated>:1)	MOVQ	BP, 24(SP)
	0x0018 00024 (<autogenerated>:1)	LEAQ	24(SP), BP
	0x001d 00029 (<autogenerated>:1)	MOVQ	32(CX), BX
	0x0021 00033 (<autogenerated>:1)	TESTQ	BX, BX
	0x0024 00036 (<autogenerated>:1)	JNE	106
	0x0026 00038 (<autogenerated>:1)	NOP
	0x0026 00038 (<autogenerated>:1)	FUNCDATA	$0, gclocals·e6397a44f8e1b6e77d0f200b4fba5269(SB)
	0x0026 00038 (<autogenerated>:1)	FUNCDATA	$1, gclocals·69c1753bd5f81501d95132d08af04464(SB)
	0x0026 00038 (<autogenerated>:1)	MOVQ	""..this+40(SP), AX                             # check pointer receiver is not nil, or panic()
	0x002b 00043 (<autogenerated>:1)	TESTQ	AX, AX
	0x002e 00046 (<autogenerated>:1)	JEQ	92
	0x0030 00048 (<autogenerated>:1)	MOVL	(AX), AX                                        # dereference pointer receiver
	0x0032 00050 (<autogenerated>:1)	MOVL	AX, (SP)                                        # move/copy resulting value to arg #1
	0x0035 00053 (<autogenerated>:1)	MOVL	"".a+48(SP), AX                                 # move/copy arg #2, #3 then call the wrappee
	0x0039 00057 (<autogenerated>:1)	MOVL	AX, 4(SP)
	0x003d 00061 (<autogenerated>:1)	MOVL	"".b+52(SP), AX
	0x0041 00065 (<autogenerated>:1)	MOVL	AX, 8(SP)
	0x0045 00069 (<autogenerated>:1)	PCDATA	$0, $1
	0x0045 00069 (<autogenerated>:1)	CALL	"".Adder.AddVal(SB)                             # call wrapped method
	0x004a 00074 (<autogenerated>:1)	MOVL	16(SP), AX                                      # copy return value from wrapped method then return
	0x004e 00078 (<autogenerated>:1)	MOVL	AX, "".~r2+56(SP)
	0x0052 00082 (<autogenerated>:1)	MOVQ	24(SP), BP
	0x0057 00087 (<autogenerated>:1)	ADDQ	$32, SP
	0x005b 00091 (<autogenerated>:1)	RET
	0x005c 00092 (<autogenerated>:1)	PCDATA	$0, $1
	0x005c 00092 (<autogenerated>:1)	CALL	runtime.panicwrap(SB)
	0x0061 00097 (<autogenerated>:1)	UNDEF
	0x0063 00099 (<autogenerated>:1)	NOP
	0x0063 00099 (<autogenerated>:1)	PCDATA	$0, $-1
	0x0063 00099 (<autogenerated>:1)	CALL	runtime.morestack_noctxt(SB)
	0x0068 00104 (<autogenerated>:1)	JMP	0
	0x006a 00106 (<autogenerated>:1)	LEAQ	40(SP), DI
	0x006f 00111 (<autogenerated>:1)	CMPQ	(BX), DI
	0x0072 00114 (<autogenerated>:1)	JNE	38
	0x0074 00116 (<autogenerated>:1)	MOVQ	SP, (BX)
	0x0077 00119 (<autogenerated>:1)	JMP	38
	0x0000 64 48 8b 0c 25 00 00 00 00 48 3b 61 10 76 54 48  dH..%....H;a.vTH
	0x0010 83 ec 20 48 89 6c 24 18 48 8d 6c 24 18 48 8b 59  .. H.l$.H.l$.H.Y
	0x0020 20 48 85 db 75 44 48 8b 44 24 28 48 85 c0 74 2c   H..uDH.D$(H..t,
	0x0030 8b 00 89 04 24 8b 44 24 30 89 44 24 04 8b 44 24  ....$.D$0.D$..D$
	0x0040 34 89 44 24 08 e8 00 00 00 00 8b 44 24 10 89 44  4.D$.......D$..D
	0x0050 24 38 48 8b 6c 24 18 48 83 c4 20 c3 e8 00 00 00  $8H.l$.H.. .....
	0x0060 00 0f 0b e8 00 00 00 00 eb 96 48 8d 7c 24 28 48  ..........H.|$(H
	0x0070 39 3b 75 b2 48 89 23 eb ad                       9;u.H.#..
	rel 5+4 t=16 TLS+0
	rel 70+4 t=8 "".Adder.AddVal+0
	rel 93+4 t=8 runtime.panicwrap+0
	rel 100+4 t=8 runtime.morestack_noctxt+0
```

Implicit dereferencing (Call value method with pointer)

- the receiver is on the stack: copy value over to the callee's stack
- the receiver is on the heap: use a wrapper function broker

## How interface built

```go
type iface struct {
    tab  *itab          // describe both the type of interface as well as the type of the data it points to
    data unsafe.Pointer // raw pointer to the value held by the interface
}

type itab struct {
    inter *interfacetype
    _type *_type
    hash  uint32 // copy of _type.hash. Used for type switches
    _     [4]byte
    fun   [1]uintptr // variable sized. func[0]==0 means _type does not implement inter.
}

type _type struct {
    size       uintptr
    ptrdata    uintptr // size of memory prefix holding all pointers
    hash       uint32
    tflag      tflag
    align      uint8
    fieldalign uint8
    kind       uint8
    alg        *typeAlg
    // gcdata stores the GC type data for the garbage collector.
    // If the kindGCProg bit is set in kind, gcdata is a GC program.
    // Otherwise it is a ptrmask bitmap. See mbitmap.go for details.
    gcdata     *byte
    str        nameOff
    ptrToThis  typeOff
}

type interfacetype struct {
    type    _type
    pkgpath name
    mhdr    []imethod
}

type imethod struct {
    name  nameOff
    itype typeOff
}

func convT2I32(tab *itab, val uint32) (i iface) {
	t := tab._type
	var x unsafe.Pointer
	if val == 0 {
		x = unsafe.Pointer(&zeroVal[0])
	} else {
		x = mallocgc(4, t, false)
		*(*uint32)(x) = val
	}
	i.tab = tab
	i.data = x
	return
}
```

1. heap allocation as the compiler takes the conservative route and forces the
   receiver to escape. this holds true even for scalar types!


## Dynamic dispatch

```go
package main

type Mather interface {
	Add(a, b int32) int32
	Sub(a, b int64) int64
}

type Adder struct{ id int32 }

//go:noinline
func (adder Adder) Add(a, b int32) int32 { return a + b }

//go:noinline
func (adder Adder) Sub(a, b int64) int64 { return a - b }

func main() {
	m := Mather(Adder{id: 6754})
	m.Add(10, 32)
}
```

```asm
	0x0000 00000 (t.go:16)	TEXT	"".main(SB), $48-0
	0x0000 00000 (t.go:16)	MOVQ	(TLS), CX
	0x0009 00009 (t.go:16)	CMPQ	SP, 16(CX)
	0x000d 00013 (t.go:16)	JLS	108
	0x000f 00015 (t.go:16)	SUBQ	$48, SP
	0x0013 00019 (t.go:16)	MOVQ	BP, 40(SP)
	0x0018 00024 (t.go:16)	LEAQ	40(SP), BP
	0x001d 00029 (t.go:16)	FUNCDATA	$0, gclocals·33cdeccccebe80329f1fdbee7f5874cb(SB)
	0x001d 00029 (t.go:16)	FUNCDATA	$1, gclocals·33cdeccccebe80329f1fdbee7f5874cb(SB)
	0x001d 00029 (t.go:17)	MOVL	$6754, ""..autotmp_1+36(SP)                             # create an addressable $6754 value at 36(SP)
	0x0025 00037 (t.go:17)	LEAQ	go.itab."".Adder,"".Mather(SB), AX                      # set up go.itab."".Adder,"".Mather
	0x002c 00044 (t.go:17)	MOVQ	AX, (SP)                                                # as first argument (tab *itab)
	0x0030 00048 (t.go:17)	LEAQ	""..autotmp_1+36(SP), AX                                # set up &36(SP)
	0x0035 00053 (t.go:17)	MOVQ	AX, 8(SP)                                               # as second argument (val unsafe.Pointer)
	0x003a 00058 (t.go:17)	PCDATA	$0, $0
	0x003a 00058 (t.go:17)	CALL	runtime.convT2I32(SB)                                   # func convT2I32(tab *itab, val uint32) (i iface)
	0x003f 00063 (t.go:17)	MOVQ	16(SP), AX                                              # AX now holds i.tab
	0x0044 00068 (t.go:17)	MOVQ	24(SP), CX                                              # CX now holds i.data
	0x0049 00073 (t.go:18)	MOVQ	24(AX), AX                                              # AX now holds iface.tab.fun[0]
	0x004d 00077 (t.go:18)	MOVQ	$137438953482, DX                                       # move (32,10) to
	0x0057 00087 (t.go:18)	MOVQ	DX, 8(SP)                                               # the top of the stack (argument #3 & #2)
	0x005c 00092 (t.go:18)	MOVQ	CX, (SP)
	0x0060 00096 (t.go:18)	PCDATA	$0, $0
	0x0060 00096 (t.go:18)	CALL	AX                                                      # call func (adder Adder) Add(a, b int32) int32
	0x0062 00098 (t.go:19)	MOVQ	40(SP), BP
	0x0067 00103 (t.go:19)	ADDQ	$48, SP
	0x006b 00107 (t.go:19)	RET
	0x006c 00108 (t.go:19)	NOP
	0x006c 00108 (t.go:16)	PCDATA	$0, $-1
	0x006c 00108 (t.go:16)	CALL	runtime.morestack_noctxt(SB)
	0x0071 00113 (t.go:16)	JMP	0
```

## Measurement

### cpu cache

```bash
$ LC_ALL=C lscpu | sed -nr '/Model name/ s/.*:\s*(.* @ .*)/\1/p'
Intel(R) Core(TM) i5-5200U CPU @ 2.20GHz

$ LC_ALL=C lscpu | grep cache
L1d cache:           32K
L1i cache:           32K
L2 cache:            256K
L3 cache:            3072K
```

### perf statistic cpu IPC (instruction per cycle) and branch predication

```bash
$ sudo perf stat --cpu=1 taskset 2 go test strings
ok  	strings	0.374s

 Performance counter stats for 'CPU(s) 1':

       2383.219835      cpu-clock (msec)          #    1.000 CPUs utilized
             3,580      context-switches          #    0.002 M/sec
                 1      cpu-migrations            #    0.000 K/sec
            81,287      page-faults               #    0.034 M/sec
     6,334,739,153      cycles                    #    2.658 GHz
    12,101,423,420      instructions              #    1.91  insn per cycle
     2,450,948,828      branches                  # 1028.419 M/sec
        41,058,516      branch-misses             #    1.68% of all branches

       2.383249218 seconds time elapsed
```

## Special cases & compiler tricks

### emtpy interface

```go
type eface struct { // 16 bytes on linux/amd64
    _type *_type         // holds the type information of the value pointed by data
    data  unsafe.Pointer
}
```

- Since the empty interface has no methods, everything related to dynamic
  dispatch can safely be dropped from the datastructure.

- With the virtual table gone, the type of the empty interface itself, not to be
  confused with the type of the data it holds, is always the same

### interface holding a scalar type

```go
func BenchmarkEfaceScalar(b *testing.B) {
    var Uint uint32
    b.Run("uint32", func(b *testing.B) {
        for i := 0; i < b.N; i++ {
            Uint = uint32(i)
        }
    })
    var Eface interface{}
    b.Run("eface32", func(b *testing.B) {
        for i := 0; i < b.N; i++ {
            Eface = uint32(i)
        }
    })
}
```

```bash
$ go test -bench=. -benchmem scalar_eface_test.go
BenchmarkEfaceScalar/uint32-4         	2000000000	         0.41 ns/op	       0 B/op	       0 allocs/op
BenchmarkEfaceScalar/eface32-4        	100000000	        18.4 ns/op	       4 B/op	       1 allocs/op
```

### byte-sized values

```go
func BenchmarkEfaceScalar(b *testing.B) {
    b.Run("eface8", func(b *testing.B) {
        for i := 0; i < b.N; i++ {
            // LEAQ    type.uint8(SB), BX
            // MOVQ    BX, (CX)
            // MOVBLZX AL, SI
            // LEAQ    runtime.staticbytes(SB), R8
            // ADDQ    R8, SI
            // MOVL    runtime.writeBarrier(SB), R9
            // LEAQ    8(CX), DI
            // TESTL   R9, R9
            // JNE     100
            // MOVQ    SI, 8(CX)
            // JMP     40
            // MOVQ    AX, R9
            // MOVQ    SI, AX
            // CALL    runtime.gcWriteBarrier(SB)
            // MOVQ    R9, AX
            // JMP     40
            Eface = uint8(i)
        }
    })
}

// staticbytes is used to avoid convT2E for byte-sized values.
var staticbytes = [...]byte{
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
    0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
    0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf,
    0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf,
    0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf,
    0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf,
    0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef,
    0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff,
}
```

Using the right offset into this array, the compiler can effectively avoid an
extra heap allocation and still reference any value representable as a single
byte.

### zero-values

when in need of a pointer to a zero-value, unnecessary allocations are avoided
by taking the address of a special, always-zero variable exposed by the runtime.

```go
//go:linkname zeroVal runtime.zeroVal
var zeroVal uintptr

type eface struct{ _type, data unsafe.Pointer }

func main() {
    x := 42
    var i interface{} = x - x // outsmart the compiler (avoid static inference)

    fmt.Printf("zeroVal = %p\n", &zeroVal)
    fmt.Printf("      i = %p\n", ((*eface)(unsafe.Pointer(&i))).data)
}
```

```bash
$ go run zeroval.go
zeroVal = 0x5458e0
      i = 0x5458e0
```

### zero-sized variable

In a similar vein as zero-values, a very common trick in Go programs is to rely
on the fact that instanciating an object of size 0 (such as struct{}{}) doesn't
result in an allocation.

Golang specification explains:

```text
A struct or array type has size zero if it contains no fields (or elements,
respectively) that have a size greater than zero. Two distinct zero-size
variables may have the same address in memory.
```

```go
//go:linkname zerobase runtime.zerobase
var zerobase uintptr

func main() {
    var s struct{}
    var a [42]struct{}

    fmt.Printf("zerobase = %p\n", &zerobase)
    fmt.Printf("       s = %p\n", &s)
    fmt.Printf("       a = %p\n", &a)
}
```

```bash
$ go run zerobase.go
zerobase = 0x546fa8
       s = 0x546fa8
       a = 0x546fa8
```

## Interface composition

Syntastic sugar exposed by the compiler.

## Type assertions & switches
