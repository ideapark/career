#!/bin/sh

#
# Copyright (c) Zhou Peng <p@ctriple.cn>
#

#
# HOWTO
#
#       main.c    vector.h
#          |         |
#      +-------------------+
#      |     compiler      |
#      |  (cpp,cc1,as)     |
#      +-------------------+        libc.so
#               |                 libvector.so
#            main.o                    |
#               |                      |
#          +-------------------------------+
#          |        linker (ld)            |
#          +-------------------------------+
#                |
#                p2
#                |
#        +------------------+
#        |  loader (execve) |        libc.so
#        +------------------+      libvector.so
#                |                     | data/text
#                |                     |
#        +---------------------------------+
#        | dynamic linker (ld-linux.so)    |
#        +---------------------------------+

gcc -shared -fPIC -o libvector.so addvec.c multvec.c
gcc -o p2 main.c ./libvector.so
