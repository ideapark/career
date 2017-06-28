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
// disable inline, display optimization infos
go build -gcflags "-l -m"
# command-line-arguments
./escape.go:5: &i escapes to heap
./escape.go:4: moved to heap: i

// disassembly to confirm
go tool objdump -s "main.main" escape
TEXT main.main(SB) /home/lockrecv/go/src/ctriple.com/more/lang/go/gotraps/escape.go
	escape.go:8	0x44d6a0	64488b0c25f8ffffff	FS MOVQ FS:0xfffffff8, CX
	escape.go:8	0x44d6a9	483b6110		CMPQ 0x10(CX), SP
	escape.go:8	0x44d6ad	765e			JBE 0x44d70d
	escape.go:8	0x44d6af	4883ec20		SUBQ $0x20, SP
	escape.go:8	0x44d6b3	48896c2418		MOVQ BP, 0x18(SP)
	escape.go:8	0x44d6b8	488d6c2418		LEAQ 0x18(SP), BP
	escape.go:9	0x44d6bd	e88effffff		CALL main.wantInt(SB)
	escape.go:9	0x44d6c2	488b0424		MOVQ 0(SP), AX
	escape.go:9	0x44d6c6	4889442410		MOVQ AX, 0x10(SP)
	escape.go:10	0x44d6cb	488b08			MOVQ 0(AX), CX
	escape.go:10	0x44d6ce	48894c2408		MOVQ CX, 0x8(SP)
	escape.go:10	0x44d6d3	e81860fdff		CALL runtime.printlock(SB)
	escape.go:10	0x44d6d8	488b442410		MOVQ 0x10(SP), AX
	escape.go:10	0x44d6dd	48890424		MOVQ AX, 0(SP)
	escape.go:10	0x44d6e1	e81a69fdff		CALL runtime.printpointer(SB)
	escape.go:10	0x44d6e6	e85562fdff		CALL runtime.printsp(SB)
	escape.go:10	0x44d6eb	488b442408		MOVQ 0x8(SP), AX
	escape.go:10	0x44d6f0	48890424		MOVQ AX, 0(SP)
	escape.go:10	0x44d6f4	e87767fdff		CALL runtime.printint(SB)
	escape.go:10	0x44d6f9	e8a262fdff		CALL runtime.printnl(SB)
	escape.go:10	0x44d6fe	e87d60fdff		CALL runtime.printunlock(SB)
	escape.go:11	0x44d703	488b6c2418		MOVQ 0x18(SP), BP
	escape.go:11	0x44d708	4883c420		ADDQ $0x20, SP
	escape.go:11	0x44d70c	c3			RET
	escape.go:8	0x44d70d	e87e85ffff		CALL runtime.morestack_noctxt(SB)
	escape.go:8	0x44d712	eb8c			JMP main.main(SB)
*/
