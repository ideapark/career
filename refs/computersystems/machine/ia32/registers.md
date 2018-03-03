# IA 32 Registers

     3                1
     1                5      8 7       0
    +----------------------------------+
    |                +-----------------|
    |%eax         %ax|   %ah  |   %al  |
    |                +-----------------|
    +----------------------------------+

    +----------------------------------+
    |                +-----------------|
    |%ecx         %cx|   %ch  |   %cl  |
    |                +-----------------|
    +----------------------------------+

    +----------------------------------+
    |                +-----------------|
    |%edx         %dx|   %dh  |   %dl  |
    |                +-----------------|
    -----------------------------------+

    +----------------------------------+
    |                +-----------------|
    |%ebx         %bx|   %bh  |   %bl  |
    |                +-----------------|
    +----------------------------------+

    +----------------------------------+
    |                +-----------------|
    |%esi         %si|                 |
    |                +-----------------|
    +----------------------------------+

    +----------------------------------+
    |                +-----------------|
    |%edi         %di|                 |
    |                +-----------------|
    +----------------------------------+

    +----------------------------------+
    |                +-----------------|
    |%esp         %sp|                 | stack pointer
    |                +-----------------|
    +----------------------------------+

    +----------------------------------+
    |                +-----------------|
    |%ebp         %bp|                 | frame pointer
    |                +-----------------|
    +----------------------------------+

# Convention

int P(int x)
{
  int y = x * x;
  int z = Q(y);
  return (y + z);
}

P calculates y before calling Q, P must ensure y is accessable after Q return,
There are two ways to get that:

- push y into P's stack frame before calling Q, after Q returned, P can pop y
  from its own stack. In other words, caller P saves the value y.

- move y to register which is saved by callee Q. If Q or other function called
  by Q want to use the same register, the callee must save this value in stack
  frame, and resume this value before he returns. When Q return to P, y is right
  here in the register. In other words, the callee is responsable for saving y.
  When Q return to P, y is resumed from the callee stack frame or y is never
  changed in the register.
