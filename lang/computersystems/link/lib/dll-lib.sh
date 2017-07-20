#!/bin/sh

#
# Copyright (c) Zhou Peng <p@ctriple.cn>
#

gcc -shared -fPIC -o libvector.so addvec.c multvec.c
gcc -rdynamic -O2 -o p2 dll.c -ldl
