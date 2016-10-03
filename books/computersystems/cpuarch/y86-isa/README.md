Y86 Instruction-Set Architecture
================================

Y86 Programmer Status
---------------------

    RF: register              CC: status code           Stat: program status
    +--------+--------+     +------+------+------+    +------------------------+
    |  %eax  |  %esi  |     |  ZF  |  SF  |  OF  |    |                        |
    +--------+--------+     +------+------+------+    +------------------------+
    |  %ecx  |  %edi  |
    +--------+--------+             PC                        DMEM: memory
    |  %edx  |  %esp  |     +--------------------+    +------------------------+
    +--------+--------+     |                    |    |                        |
    |  %ebx  |  %ebp  |     +--------------------+    |                        |
    +--------+--------+                               +------------------------+

Y86 Instruction Set
-------------------

    +-----------------------------------------------------------+
    | Byte                  0     1     2     3     4     5     |
    |                                                           |
    | halt                 |0 |0 |                              |
    |                                                           |
    | nop                  |1 |0 |                              |
    |                                                           |
    | rrmovl rA,rB         |2 |0 |rA|rB|                        |
    |                                                           |
    | irmovl V,rB          |3 |0 |F |rB|        V          |    |
    |                                                           |
    | rmmovl rA,D(rB)      |4 |0 |rA|rB|        D          |    |
    |                                                           |
    | mrmovl D(rB),rA      |4 |0 |rA|rB|        D          |    |
    |                                                           |
    | OPl rA,rB            |5 |0 |rA|rB|                        |
    |                                                           |
    | jXX Dest             |6 |fn|rA|rB|                        |
    |                                                           |
    | cmovXX rA,rB         |7 |fn|        Dest         |        |
    |                                                           |
    | call Dest            |2 |fn|rA|rB|                        |
    |                                                           |
    | ret                  |9 |0 |                              |
    |                                                           |
    | pushl rA             |A |0 |rA|F |                        |
    |                                                           |
    | popl rA              |B |0 |rA|F |                        |
    +-----------------------------------------------------------+

Instruction Coding
------------------

            Integer                Branch                 Transfer

            +---+             +---+      +---+              +---+         +---+
       addl |6|0|         jmp |7|0|  jne |7|4|       rrmovl |2|0|  cmovne |2|4|
            +---+             +---+      +---+              +---+         +---+

            +---+             +---+      +---+              +---+         +---+
       subl |6|1|         jle |7|1|  jge |7|5|       cmovle |2|1|  cmovge |2|5|
            +---+             +---+      +---+              +---+         +---+

            +---+             +---+      +---+              +---+         +---+
       andl |6|2|         jl  |7|2|  jg  |7|6|       cmovl  |2|2|  cmovg  |2|6|
            +---+             +---+      +---+              +---+         +---+

            +---+             +---+                         +---+
       xorl |6|3|         je  |7|3|                  cmove  |2|3|
            +---+             +---+                         +---+

Y86 Exception
-------------

    +-------+------+----------------------------+
    | Value | Name | Meaning                    |
    +-------+------+----------------------------+
    |   1   | AOK  | Normal Operation           |
    +-------+------+----------------------------+
    |   2   | HLT  | Executing halt instruction |
    +-------+------+----------------------------+
    |   3   | ADR  | Illegal address            |
    +-------+------+----------------------------+
    |   4   | INS  | Illegal instruction        |
    +-------+------+----------------------------+

Y86 Program
-----------

> int Sum(int *Start, int Count)
> {
>    int sum = 0;
>    while (Count) {
>        sum += *Start;
>        Start++;
>        Count--;
>    }
>
>    return sum;
> }

    +---------------------------------------------------------------------------------------+
    | IA32 code                                    Y86 code                                 |
    |                                                                                       |
    |    int Sum(int *Start, int Count)               int Sum(int *Start, int Count)        |
    | 1    Sum:                                    1    Sum:                                |
    | 2      pushl %ebp                            2      pushl %ebp                        |
    | 3      movl %esp,%ebp                        3      rrmovl %esp,%ebp                  |
    | 4      movl 8(%ebp),%ecx  ;ecx=Start         4      mrmovl 8(%ebp),%ecx  ;ecx=Start   |
    | 5      movl 12(%ebp),%edx ;edx=Count         5      mrmovl 12(%ebp),%edx ;edx=Count   |
    | 6      xorl %eax,%eax     ;sum=0             6      xorl %eax,%eax       ;sum=0       |
    | 7      testl %edx,%edx                       7      andl %edx,%edx                    |
    | 8      je .L34                               8      je End                            |
    | 9    .L35:                                   9    Loop:                               |
    | 10     addl (%ecx),%eax   ;add *Start to sum 10     mrmovl (%ecx),%esi   ;get *Start  |
    |                                              11     addl %esi,%eax       ;add to sum  |
    | 11     addl $4,%ecx       ;Start++           12     irmovl $4,%ebx                    |
    |                                              13     addl %ebx,%ecx       ;Start++     |
    | 12     decl %edx          ;Count--           14     irmovl $-1,%ebx                   |
    |                                              15     addl %ebx,%edx       ;Count--     |
    | 13     jnz .L35           ;Stop when 0       16     jne Loop             ;Stop when 0 |
    | 14   .L34:                                   17   End:                                |
    | 15     movl %ebp,%esp                        18     rrmovl %ebp,%esp                  |
    | 16     popl %ebp                             19     popl %ebp                         |
    | 17     ret                                   20     ret                               |
    +---------------------------------------------------------------------------------------+
