#!/bin/sh

insmod hello.ko mystring="bebop" mybyte=255 myintArray=-1
rmmod hello.ko
dmesg | tail -n 9
echo ""

insmod hello.ko mystring="supercalifragilisticexpialidocious" mybyte=256 myintArray=-1,-1
rmmod hello.ko
dmesg | tail -n 9
echo ""

insmod hello.ko mylong=hello
dmesg | tail -n 9
