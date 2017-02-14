#!/bin/env bash

# diff gcc -fomit-frame-pointer and -fno-omit-frame-pointer assembly code
diff -y <(gcc -S -fomit-frame-pointer code.c -o -) <(gcc -S -fno-omit-frame-pointer code.c -o -)
