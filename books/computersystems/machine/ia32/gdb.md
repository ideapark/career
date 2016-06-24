# GDB Manual

    +---------------------------+-------------------------------------------------+
    |          Command          |                Description                      |
    +---------------------------+-------------------------------------------------+
    |         Start & Stop      |                                                 |
    | quit                      | quit GDB                                        |
    | run                       | run  program (with command line arguments)      |
    | kill                      | stop program                                    |
    +---------------------------+-------------------------------------------------+
    |         Break Point       |                                                 |
    | break sum                 | set breakpoint at the entrance of function sum  |
    | break *0x8048394          | set breakpoint at address 0x8048394             |
    | delete 1                  | delete breakpoint 1                             |
    | delete                    | delete all breakpoints                          |
    +---------------------------+-------------------------------------------------+
    |         Execute           |                                                 |
    | setpi                     | execute one instruction                         |
    | setpi 4                   | execute 4 instructions                          |
    | nexti                     | similar to setpi, by function call times        |
    | continue                  | continue to execute                             |
    | finish                    | run to end of function                          |
    +---------------------------+-------------------------------------------------+
    |         Check Code        |                                                 |
    | disas                     | disassembly current function                    |
    | disas sum                 | disassembly function sum                        |
    | disas 0x8048397           | disassembly function near by address 0x8048397  |
    | disas 0x8048394 0x80483a4 | disassembly address from 0x8048394 to 0x80483a4 |
    | print /x $eip             | display register eip value in hexadecimal       |
    +---------------------------+-------------------------------------------------+
    |         Check Data        |                                                 |
    | print $eax                | display register eax in decimal                 |
    | print /x $eax             | display register eax in hexadecimal             |
    | print /t $eax             | display register eax in binary                  |
    | print 0x100               | display 0x100 in decimal                        |
    | print /x 555              | display 555 in hexadecimal                      |
    | print /x ($ebp+8)         | display ebp + 8 in hexadecimal                  |
    | print *(int *) 0xfff076b0 | display integer value at address 0xfff076b0     |
    | print *(int *) ($ebp+8)   | display integer value at address ebp+8          |
    | x/2w 0xfff076b0           | check 4 bytes start from address 0xfff076b0     |
    | x/20b sum                 | check 20 bytes before sum                       |
    +---------------------------+-------------------------------------------------+
    |         Info              |                                                 |
    | info frame                | current frame information                       |
    | info registers            | display all registers value                     |
    | help                      | GDB help info                                   |
    +---------------------------+-------------------------------------------------+
