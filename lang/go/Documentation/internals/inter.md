# Interface

## example code

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

## how interface built

## dynamic dispatch

## special cases

## interface composition

## type assertions & switches
