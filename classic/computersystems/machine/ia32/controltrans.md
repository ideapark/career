# Procedure Call Instruction

    --------------------------------------
    |   Instruction   |   Description    |
    |------------------------------------|
    | call   Label    | call procedure   |
    | call   *Operand | call procedure   |
    | leave           | prepare for ret  |
    | ret             | return to caller |
    --------------------------------------

# Assembly code

    ;beginning of function sum
    08048394 <sum>:
    08048394:  55                push %ebp

    ...

    ;return from function sum
    080483a4:  c3                ret

    ...

    ;call to sum from main
    080483dc:  e8 b3 ff ff ff    call 8048394 <sum>
    080483e1:  83 c4 14          add  $0x14,%esp

# call & ret

                      ---------------------
                      | %eip | 0x080483dc |
                  --- | %esp | 0xff9bc960 |
                  |   ---------------------
                  |
    call before   |   ---------------------
                  |   |                   |
                  |   |        *          |
                  |   |                   |
                  |   |        *          |
                  |   |                   |
                  |   |        *          |
                  |   |                   |
                  --> ---------------------

                      ---------------------
                      | %eip | 0x08048394 |
                  --- | %esp | 0xff9bc95c |
                  |   ---------------------
                  |
    call after    |   ---------------------
                  |   |                   |
                  |   |        *          |
                  |   |                   |
                  |   |        *          |
                  |   |                   |
                  |   |        *          |
                  |   |                   |
                  |   |-------------------|
                  |   |    0x080483e1     |
                  --> ---------------------

                   *

                   *

                   *

                      ---------------------
                      | %eip | 0x080483e1 |
                  --- | %esp | 0xff9bc960 |
                  |   ---------------------
                  |
    ret  after    |   ---------------------
                  |   |                   |
                  |   |        *          |
                  |   |                   |
                  |   |        *          |
                  |   |                   |
                  |   |        *          |
                  |   |                   |
                  --> ---------------------

- *call* instruction transfer control to callee's start address.
- *ret* instruction transfer control to instruction right after caller's call instruction.
