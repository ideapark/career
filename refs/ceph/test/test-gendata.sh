#!/usr/bin/bash

# This script generate sized random data file

test -d testdata || mkdir testdata

for size in 1K 10K 1M 10M 100M 500M 1G
do
    echo "GENDATA ===>> $size"
    head -c $size < /dev/urandom > testdata/test-${size}.dat
done
