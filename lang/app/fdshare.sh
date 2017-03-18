#!/bin/sh

read line; echo p: $line    # read a line in parent shell, print it
(read line; echo c: $line)  # read a line in child shell, print it
read line; echo p: $line    # read a line in parent shell, print it
