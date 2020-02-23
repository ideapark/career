#!/bin/bash

gcc -Wall -g mtrace.c -o mtrace.out        # compile with debug information
MALLOC_TRACE=/tmp/mtrace.log ./mtrace.out  # enable mtrace log file
mtrace ./mtrace.out /tmp/mtrace.log        # using mtrace to analyze log file
rm -rf mtrace.out /tmp/mtrace.log          # clear environment
