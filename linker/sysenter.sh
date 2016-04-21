#!/bin/sh

# Virtual dynamic shared library
cat /proc/self/maps | grep \[vdso\]

dd if=/proc/self/mem of=linux-gate.dso bs=4096 skip=1048574 count=1

objdump -T linux-gate.dso | grep __kernel_vsyscall

objdump -d --start-address=0xffffe400 --stop-address=0xffffe408 linux-gate.dso | grep sysenter
