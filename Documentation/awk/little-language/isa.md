# ASSEMBLY-LANGUAGE INSTRUCTION

```text
================================================================================
 OPCODE |  INSTRUCTION  |               MEANING
--------+---------------+-------------------------------------------------------
   01   | get           | read a number from the input into the accumulator
   02   | put           | write the contents of the accumulator to the output
   03   | ld M          | load accumulator with contents of memory location M
   04   | st M          | store contents of accumulator in location M
   05   | add M         | add contents of location M to accumulator
   06   | sub M         | subtract contents of location M from accumulator
   07   | jpos M        | jump to location M if accumulator is positive
   08   | jz M          | jump to location M if accumulator is zero
   09   | j M           | jump to location M
   10   | halt          | stop execution
        | const C       | assembler pseudo-operation to define a constant C
--------+---------------+-------------------------------------------------------
```
