#!/bin/sh

mkfifo test_fifo            # create a fifo file

if [ -p test_fifo ]; then
    stat test_fifo
fi

cat < test_fifo &           # start a reader in the background

echo "It was a Blustery Day" > test_fifo  # send data to fifo

rm test_fifo                # remove test fifo
