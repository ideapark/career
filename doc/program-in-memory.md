# Kernel/User Space

     Linux User/Kernel                   Windows, default                    Windows booted
       Memory Split                        Memory Split                     with /3GB switch
    +-----------------+0xffffffff      +-----------------+0xffffffff       +-----------------+0xffffffff
    |   Kernel Space  |                |                 |                 |   Kernel Space  |
    |       (1GB)     |                |   Kernel Space  |                 |      (1GB)      |
    +-----------------+0xc0000000      |       (2GB)     |                 +-----------------+0xc0000000
    |                 |                |                 |                 | User Mode Space |
    |                 |                +-----------------+0x80000000       |      (3GB)      |
    | User Mode Space |                |                 |                 | Only applies to |
    |      (3GB)      |                | User Mode Space |                 | EXEs flagged as |
    |                 |                |       (2GB)     |                 |  large-address  |
    |                 |                |                 |                 |     aware.      |
    +-----------------+0               +-----------------+0                +-----------------+


# Process Switches

    +-----------------+0xffffffff       +-----------------+0xffffffff       +-----------------+0xffffffff
    |   Kernel Space  |                 |   Kernel Space  |                 |   Kernel Space  |
    |       (1GB)     |                 |       (1GB)     |                 |       (1GB)     |
    +-----------------+0xc0000000       +-----------------+0xc0000000       +-----------------+0xc0000000
    |*****************|                 |*****************|                 |*****************|
    |                 |                 |                 |                 |                 |
    | User Mode Space |     Process     | User Mode Space |     Process     | User Mode Space |
    |****(Firefox)****|     Switch      |     (/bin/ls)   |     Switch      |*****(Firefox)***|
    |*****************|  ------------>  |                 |  ------------>  |*****************|
    |*****************|                 |*****************|                 |*****************|
    +-----------------+0                +-----------------+0                +-----------------+0


# Segment Layout

      --->+-----------------------------------------------------------+
      |   |                       Kernel space                        |
     1GB  |  User code CANNOT read from nor write to these address,   |
      |   |         doing so results in a Segmentation Fault          |
      --->+-----------------------------------------------------------+0xc0000000 == TASK_SIZE
      |   |                                                           |
      |   |                                                           | Random stack offset
      |   +-----------------------------------------------------------+<---
      |   |                       Stack (grows down)                  |   |
      |   |                             ||                            |   |
      |   |                             \/                            |  RLIMIT_STACK (e.g., 8MB)
      |   +-----------------------------------------------------------+   |
      |   |                                                           |   |
      |   |                                                           |<---
      |   |                                                           |   |
      |   |                                                           |  Random mmap offset
      |   |                                                           |   |
      |   +-----------------------------------------------------------+<---
      |   |                    Memory Mapping Segment                 |
      |   | File mappings (including dynamic libraries) and anonymous |
      |   |              mappings. Example: /lib/libc.so              |
      |   |                             ||                            |
      |   |                             ||                            |
      |   |                             \/                            |
     3GB  +-----------------------------------------------------------+
      |   |                                                           |
      |   |                                                           |
      |   |                                                           |program break
      |   +-----------------------------------------------------------+
      |   |                             /\                            |brk
      |   |                             ||                            |
      |   |                             ||                            |
      |   |                            Heap                           |start brk
      |   +-----------------------------------------------------------+<---
      |   |                                                           |   |
      |   |                                                           |  Random brk offset
      |   |                                                           |   |
      |   +-----------------------------------------------------------+<---
      |   |                          BSS segment                      |
      |   |   Uninitialized static variables, filled with zeros       |
      |   |              Example: static char *userName;              |
      |   +-----------------------------------------------------------+end_data
      |   |                         Data segment                      |
      |   |   Static variable initialized by the programmer.          |
      |   |  Example: static char *gonzo = "God's own prototype";     |start_data
      |   +-----------------------------------------------------------+end_code
      |   |                         Text segment (ELF)                |
      |   | Stores the binary image of the process (e.g., /bin/gonzo) |
      |   +-----------------------------------------------------------+0x08048000
      |   |                                                           |
      --->+-----------------------------------------------------------+0


# Actual Segments

             Memory
    +----------------------+                        Symbol name or address
    |         BSS          |\                             in memory
    |Read/Write (anonymous)| \
    +----------------------+  \+---------------------+
    |         Data         |\  | (memory filled with |userName
    |      Read/Write      | \ |        zeros)       |cntActiveUsers  <--+
    +----------------------+  \+---------------------+                   |
    |         Text         |\  |      0x080484f0     |gonzo              |
    |      Read/Execute    | \ +---------------------+                   |
    +----------------------+  \|         10          |cntWorkBees        |
                           |   +---------------------+               Binary image on disk
                           \   |"God's own prototype"|0x080484f0        (/bin/gonzo)
                            \  +---------------------+                   |
                             \ | jmp here, jmp there |                   |
                              \| mov this, mov that  |0x08048000         |
                               +---------------------+                <--+
