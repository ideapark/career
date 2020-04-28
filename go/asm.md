# Go Assembler

## Assembly Build Rule

- Toolchain will select appropriate assembly files according to GOOS+GOARCH

Using file extensions, e.g.

  sys_linux_amd64.s
  sys_darwin_amd64.s

## Prototype

- Function declaration

[src/runtime/timestub.go](https://github.com/golang/go/blob/f639a81cd5e85ca9538c76e612867aa4c2ae241b/src/runtime/timestub2.go#L13)

- Function assembly implementation

[runtime/sys_linux_amd64.s](https://github.com/golang/go/blob/f639a81cd5e85ca9538c76e612867aa4c2ae241b/src/runtime/sys_linux_amd64.s#L209)

## Pseudo-registers

- FP: Frame Pointer

1. Points to the bottom of the argument list
2. Offsets are positive
3. Offsets must include a name, e.g. arg+0(FP)

- SP: Stack Pointer

1. Points to the top of the space allocated for local variables
2. Offsets are negative
3. Offsets must include a name, e.g. ptr-8(SP)

- SB: Static Base

1. Named offsets from a global base

## Stack Frame

- w/o frame pointer

```text
 High address
   ^
   | CALLER
   | +---------------+
   | |   arguments   |
   | +---------------+
   | |parent ret addr|
   | +---------------+
   | |     local     |
   | |   variables   |
   | |               |CALLEE
   | |               |+---------------+
   | |               ||   arguments   |
   | +---------------++---------------+ <---- FP (pseudo-register)
   | | return address||parent ret addr|
   | +---------------++---------------+ <---- SP (pseudo-register)
   |                  |    local      |     \
   |                  |   variable    |      \
   |                  |               |       \
   |                  |               |       / callee stack frame
   |                  +---------------+      /
   |                  | return address|     /
   |                  +---------------+ <---- RSP (HW-register)
   |
 Low address
```

- w/ frame pointer

```text
 High address
   ^
   | CALLER
   | +---------------+
   | |   arguments   |
   | +---------------+
   | |parent ret addr|
   | +---------------+
   | | parent frame  |
   | |   pointer     |
   | +---------------+
   | |     local     |
   | |   variables   |
   | |               |CALLEE
   | |               |+---------------+
   | |               ||   arguments   |
   | +---------------++---------------+ <---- FP (pseudo-register)
   | | return address||parent ret addr|
   | +---------------++---------------+
   | | frame pointer || parent frame  |
   | |               ||   pointer     |
   | +---------------++---------------+ <---- SP (pseudo-register)
   |                  |    local      |     \
   |                  |   variable    |      \
   |                  |               |       \
   |                  |               |        \
   |                  +---------------+        / callee stack frame
   |                  | return address|       /
   |                  +---------------+      /
   |                  | frame pointer |     /
   |                  +---------------+ <---- RSP (HW-register)
   |
 Low address
```

## Example

```go
package main

//go:noinline
func add(a, b int32) (int32, bool) {
    return a+b, true
}

func main() {
    add(10, 32)
}
```

## Assembly

```bash
GOOS=linux GOARCH=amd64 go tool compile -S t.go
```

## Annotated add & main (trimmed)

```asm
"".add STEXT nosplit size=20 args=0x10 locals=0x0
    0x0000 00000 (t.go:4)   TEXT        "".add(SB), NOSPLIT, $0-16                                   # $0-16: frameSize-argumentSize, NOSPLIT: no stack-split preamble
    0X0000 00000 (t.go:4)   FUNCDATA    $0, gclocals·f207267fbf96a0178e8758c6e3e0ce28(SB)            # GC infos, introduced by compiler
    0x0000 00000 (t.go:4)   FUNCDATA    $1, gclocals·33cdeccccebe80329f1fdbee7f5874cb(SB)
    0x0000 00000 (t.go:4)   MOVL        "".b+12(SP), AX                                              # arg b
    0x0004 00004 (t.go:4)   MOVL        "".a+8(SP), CX                                               # arg a
    0x0008 00008 (t.go:5)   ADDL        CX, AX
    0x000a 00010 (t.go:5)   MOVL        AX, "".~r2+16(SP)                                            # first return value (int32)
    0x000e 00014 (t.go:5)   MOVB        $1, "".~r3+20(SP)                                            # second return value (bool true)
    0x0013 00019 (t.go:5)   RET                                                                      # jump to return address stored in 0(SP)
    0x0000 8b 44 24 0c 8b 4c 24 08 01 c8 89 44 24 10 c6 44  .D$..L$....D$..D
    0x0010 24 14 01 c3                                      $...
"".main STEXT size=65 args=0x0 locals=0x18
    0x0000 00000 (t.go:8)   TEXT        "".main(SB), $24-0
    0x0000 00000 (t.go:8)   MOVQ        (TLS), CX                                                    # stack-split prologue
    0x0009 00009 (t.go:8)   CMPQ        SP, 16(CX)
    0x000d 00013 (t.go:8)   JLS         58
    0x000f 00015 (t.go:8)   SUBQ        $24, SP                                                      # make stack frame for main (24 = 8:uintptr + 4:aligned bool + 4:int32 + 4:int32 + 4:int32)
    0x0013 00019 (t.go:8)   MOVQ        BP, 16(SP)                                                   # save caller's BP
    0x0018 00024 (t.go:8)   LEAQ        16(SP), BP                                                   # get main stack frame's BP
    0x001d 00029 (t.go:8)   FUNCDATA    $0, gclocals·33cdeccccebe80329f1fdbee7f5874cb(SB)            # GC infos, introduced by compiler
    0x001d 00029 (t.go:8)   FUNCDATA    $1, gclocals·33cdeccccebe80329f1fdbee7f5874cb(SB)
    0x001d 00029 (t.go:9)   MOVQ        $137438953482, AX                                            # $137438953482: b:32+a:10 (int64); $echo 'obase=2;137438953482' | bc
    0x0027 00039 (t.go:9)   MOVQ        AX, (SP)
    0x002b 00043 (t.go:9)   PCDATA      $0, $0                                                       # GC infos, introduced by compiler
    0x002b 00043 (t.go:9)   CALL        "".add(SB)                                                   # also push the return address on top of the stack
    0x0030 00048 (t.go:10)  MOVQ        16(SP), BP                                                   # resume caller's BP
    0x0035 00053 (t.go:10)  ADDQ        $24, SP                                                      # destroy main stack frame
    0x0039 00057 (t.go:10)  RET
    0x003a 00058 (t.go:10)  NOP                                                                      # some platform cannot jump to call, which may lead to very dark places
    0x003a 00058 (t.go:8)   PCDATA      $0, $-1                                                      # GC infos, introduced by compiler
    0x003a 00058 (t.go:8)   CALL        runtime.morestack_noctxt(SB)                                 # stack-split epilogue
    0x003f 00063 (t.go:8)   JMP         0
    0x0000 64 48 8b 0c 25 00 00 00 00 48 3b 61 10 76 2b 48  dH..%....H;a.v+H
    0x0010 83 ec 18 48 89 6c 24 10 48 8d 6c 24 10 48 b8 0a  ...H.l$.H.l$.H..
    0x0020 00 00 00 20 00 00 00 48 89 04 24 e8 00 00 00 00  ... ...H..$.....
    0x0030 48 8b 6c 24 10 48 83 c4 18 c3 e8 00 00 00 00 eb  H.l$.H..........
    0x0040 bf                                               .
    rel 5+4 t=16 TLS+0
    rel 44+4 t=8 "".add+0
    rel 59+4 t=8 runtime.morestack_noctxt+0
```

## Stack diagram (main.add has finished executing)

```text
         +--------------------+ <-- 32(SP)
    G |  |                    |
    R |  | main.main's saved  |
    O |  |  frame-pointer (BP)|
    w |  |--------------------| <-- 24(SP)
    S |  |     [alignment]    |
      |  | "".~r3(bool)=1/true| <-- 21(SP)
    D |  |--------------------| <-- 20(SP)
    O |  | "".~r2(int32)=42   |
    W |  |--------------------| <-- 16(SP)
    N |  | "".b(int32)=32     |
    W |  |--------------------| <-- 12(SP)
    A |  | "".a(int32)=10     |
    R |  |--------------------| <--  8(SP)
    D |  |                    |
    S |  |  return address to |
      ↓  |   main.main + 0x30 |
         +--------------------+ <--  0(SP) (TOP OF STACK)
```

## Stack-split

New goroutine is given an initial tiny 2kB stack by the runtime (said stack is
actually allocated on the heap behind the scenes). As a goroutine runs along
doing its job, it might end up outgrowing its contrived, initial stack-space
(i.e. stack-overflow). To prevent this from happening, the runtime makes sure
that when a goroutine is running out of stack, a new, bigger stack with two
times the size of the old one gets allocated, and that the content of the
original stack gets copied over to the new one. This process is known as a
stack-split and effectively makes goroutine stacks dynamically-sized.

For stack-splitting to work, the compiler inserts a few instructions at the
beginning and end of every function that could potentially overflow its stack.
To avoid unnecessary overhead, functions that cannot possibly outgrow their
stack are marked as NOSPLIT as a hint for the compiler not to insert these
checks.

```asm
"".main STEXT size=65 args=0x0 locals=0x18
    0x0000 00000 (t.go:8)   TEXT        "".main(SB), $24-0
    0x0000 00000 (t.go:8)   MOVQ        (TLS), CX                                                    # stack-split prologue
    0x0009 00009 (t.go:8)   CMPQ        SP, 16(CX)                                                   # compare SP and g.stackguard0
    0x000d 00013 (t.go:8)   JLS         58                                                           # jump to epilogue if SP < g.stackguard0
    ;; ...ommited main body...
    0x003a 00058 (t.go:10)  NOP                                                                      # some platform cannot jump to call, which may lead to very dark places
    0x003a 00058 (t.go:8)   PCDATA      $0, $-1                                                      # GC infos, introduced by compiler
    0x003a 00058 (t.go:8)   CALL        runtime.morestack_noctxt(SB)                                 # stack-split epilogue
    0x003f 00063 (t.go:8)   JMP         0                                                            # jump back to start again
```

As you can see, the stack-split preamble is divided into a prologue and an
epilogue:

- The prologue checks whether the goroutine is running out of space and, if it's
  the case, jumps to the epilogue.

- The epilogue, on the other hand, triggers the stack-growth machinery and then
  jumps back to the prologue.

```go
type g struct {
	// Stack parameters.
	// stack describes the actual stack memory: [stack.lo, stack.hi).
	// stackguard0 is the stack pointer compared in the Go stack growth prologue.
	// It is stack.lo+StackGuard normally, but can be StackPreempt to trigger a preemption.
	// stackguard1 is the stack pointer compared in the C stack growth prologue.
	// It is stack.lo+StackGuard on g0 and gsignal stacks.
	// It is ~0 on other goroutine stacks, to trigger a call to morestackc (and crash).
	stack       stack   // offset known to runtime/cgo
	stackguard0 uintptr // offset known to liblink
	stackguard1 uintptr // offset known to liblink

    // ...omitted dozens of fields...
}
```
