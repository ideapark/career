#!/usr/bin/bash

# This script generate sized random data file

test -d testdata || mkdir testdata

for size in 1k 10k 1m 10m 100m 500m 1g
do
    echo "GENDATA ===>> $size"
    head -c $size < /dev/urandom > testdata/${size}.dat
done
