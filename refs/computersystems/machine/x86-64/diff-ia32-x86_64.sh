#!/bin/env bash

# diff ia32 vs x86-64 assembly code with side-by-side mode
diff -y <(gcc -O1 -S -m32 code.c -o -) <(gcc -O1 -S -m64 code.c -o -)
