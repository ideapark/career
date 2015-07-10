	.file	"IfElseIf.cpp"
.lcomm __ZStL8__ioinit,1,1
	.def	___main;	.scl	2;	.type	32;	.endef
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB971:
	.cfi_startproc
	.cfi_personality 0,___gxx_personality_v0
	.cfi_lsda 0,LLSDA971
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x7c,0x6
	subl	$36, %esp
	call	___main
	movl	$0, -12(%ebp)
	movl	$0, -16(%ebp)
	jmp	L2
L4:
	movzbl	-17(%ebp), %eax
	cmpb	$32, %al
	jne	L3
	addl	$1, -12(%ebp)
	jmp	L2
L3:
	movzbl	-17(%ebp), %eax
	cmpb	$10, %al
	jne	L2
	addl	$1, -16(%ebp)
L2:
	leal	-17(%ebp), %eax
	movl	%eax, (%esp)
	movl	$__ZSt3cin, %ecx
LEHB0:
	call	__ZNSi3getERc
	subl	$4, %esp
	movl	(%eax), %edx
	subl	$12, %edx
	movl	(%edx), %edx
	addl	%edx, %eax
	movl	%eax, %ecx
	call	__ZNKSt9basic_iosIcSt11char_traitsIcEEcvPvEv
LEHE0:
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	jne	L4
	movl	$0, %eax
	jmp	L8
L7:
	movl	%eax, (%esp)
LEHB1:
	call	__Unwind_Resume
LEHE1:
L8:
	movl	-4(%ebp), %ecx
	.cfi_def_cfa 1, 0
	leave
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE971:
	.def	___gxx_personality_v0;	.scl	2;	.type	32;	.endef
	.section	.gcc_except_table,"w"
LLSDA971:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 LLSDACSE971-LLSDACSB971
LLSDACSB971:
	.uleb128 LEHB0-LFB971
	.uleb128 LEHE0-LEHB0
	.uleb128 L7-LFB971
	.uleb128 0
	.uleb128 LEHB1-LFB971
	.uleb128 LEHE1-LEHB1
	.uleb128 0
	.uleb128 0
LLSDACSE971:
	.text
	.def	___tcf_0;	.scl	3;	.type	32;	.endef
___tcf_0:
LFB976:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	movl	$__ZStL8__ioinit, %ecx
	call	__ZNSt8ios_base4InitD1Ev
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE976:
	.def	__Z41__static_initialization_and_destruction_0ii;	.scl	3;	.type	32;	.endef
__Z41__static_initialization_and_destruction_0ii:
LFB975:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	cmpl	$1, 8(%ebp)
	jne	L10
	cmpl	$65535, 12(%ebp)
	jne	L10
	movl	$__ZStL8__ioinit, %ecx
	call	__ZNSt8ios_base4InitC1Ev
	movl	$___tcf_0, (%esp)
	call	_atexit
L10:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE975:
	.def	__GLOBAL__sub_I_main;	.scl	3;	.type	32;	.endef
__GLOBAL__sub_I_main:
LFB977:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	$65535, 4(%esp)
	movl	$1, (%esp)
	call	__Z41__static_initialization_and_destruction_0ii
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE977:
	.section	.ctors,"w"
	.align 4
	.long	__GLOBAL__sub_I_main
	.ident	"GCC: (GNU) 4.8.1"
	.def	__ZNSi3getERc;	.scl	2;	.type	32;	.endef
	.def	__ZNKSt9basic_iosIcSt11char_traitsIcEEcvPvEv;	.scl	2;	.type	32;	.endef
	.def	__Unwind_Resume;	.scl	2;	.type	32;	.endef
	.def	__ZNSt8ios_base4InitD1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZNSt8ios_base4InitC1Ev;	.scl	2;	.type	32;	.endef
	.def	_atexit;	.scl	2;	.type	32;	.endef
