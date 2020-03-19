#!/bin/bash

# generate giant file
for i in $(seq 200000); do
    echo $(date '+%s') >> /tmp/tmp_giant.txt
done

# shuffle
TMPDIR=/dev/shm shuf /tmp/tmp_giant.txt > /tmp/giant.txt

# show lines, words, letters
wc /tmp/giant.txt

# use real files
time sort /tmp/giant.txt > /dev/null

# use RAM disk
time TMPDIR=/dev/shm sort /tmp/giant.txt > /dev/null

# clear env
rm -f /tmp/giant.txt
rm -f /tmp/tmp_giant.txt
