#!/bin/sh

#
# Copyright (c) Zhou Peng <lockrecv@qq.com>
#

# HOWTO
#
# source               main.c   vector.h
#                        |         |
#                     +------------------+
#                     |      compiler    |
#                     | (cpp, cc1, as)   |
#                     +------------------+           libvector.a               libc.a      static library
#                               |                         |                       |
#  relocatable object file   main.o                       | addvec.o              | printf.o
#                               |                         |                       |
#                          +-----------------------------------------------------------+
#                          |                     linker (ld)                           |
#                          +-----------------------------------------------------------+
#                                                      |
#                                                      p2    static linked executable file

gcc -c addvec.c multvec.c
ar rcs libvector.a addvec.o multvec.o

gcc -O2 -c main.c
gcc -static -o p2 main.o ./libvector.a
