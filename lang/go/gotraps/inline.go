package main

func wantInt() *int {
	i := 0x100
	return &i
}

func main() {
	a := wantInt()
	println(a, *a)
}

/*
// inline by default, display optimization infos
go build -gcflags "-m"
# command-line-arguments
./inline.go:3: can inline wantInt
./inline.go:8: can inline main
./inline.go:9: inlining call to wantInt
./inline.go:5: &i escapes to heap
./inline.go:4: moved to heap: i
./inline.go:9: main &i does not escape

// disassembly to confirm
go tool objdump -s "main.main" inline
TEXT main.main(SB) /home/lockrecv/go/src/ctriple.com/more/lang/go/gotraps/inline.go
	inline.go:8	0x44d650	64488b0c25f8ffffff	FS MOVQ FS:0xfffffff8, CX
	inline.go:8	0x44d659	483b6110		CMPQ 0x10(CX), SP
	inline.go:8	0x44d65d	7650			JBE 0x44d6af
	inline.go:8	0x44d65f	4883ec18		SUBQ $0x18, SP
	inline.go:8	0x44d663	48896c2410		MOVQ BP, 0x10(SP)
	inline.go:8	0x44d668	488d6c2410		LEAQ 0x10(SP), BP
	inline.go:9	0x44d66d	48c744240800010000	MOVQ $0x100, 0x8(SP)
	inline.go:10	0x44d676	e87560fdff		CALL runtime.printlock(SB)
	inline.go:9	0x44d67b	488d442408		LEAQ 0x8(SP), AX
	inline.go:10	0x44d680	48890424		MOVQ AX, 0(SP)
	inline.go:10	0x44d684	e87769fdff		CALL runtime.printpointer(SB)
	inline.go:10	0x44d689	e8b262fdff		CALL runtime.printsp(SB)
	inline.go:10	0x44d68e	48c7042400010000	MOVQ $0x100, 0(SP)
	inline.go:10	0x44d696	e8d567fdff		CALL runtime.printint(SB)
	inline.go:10	0x44d69b	e80063fdff		CALL runtime.printnl(SB)
	inline.go:10	0x44d6a0	e8db60fdff		CALL runtime.printunlock(SB)
	inline.go:11	0x44d6a5	488b6c2410		MOVQ 0x10(SP), BP
	inline.go:11	0x44d6aa	4883c418		ADDQ $0x18, SP
	inline.go:11	0x44d6ae	c3			RET
	inline.go:8	0x44d6af	e8dc85ffff		CALL runtime.morestack_noctxt(SB)
	inline.go:8	0x44d6b4	eb9a			JMP main.main(SB)
*/
