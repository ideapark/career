#!/bin/bash

set -x                       # turn on execution tracing
diff -y <(ls -lF) <(ls -l)   # run command
set +x                       # turn off execution tracing

echo ''
echo '################## PROCESS SUBSTITUTION ####################'
echo '                                                            '
echo '+------+             |                                      '
echo '|ls -lF| -----> fd 1 | fd 63 ---------------+               '
echo '+------+            Pipe                    |               '
echo '                                            v               '
echo '                             +----------------------------+ '
echo '                             | diff /dev/fd/63 /dev/fd/62 | '
echo '                             +----------------------------+ '
echo '                                                       ^    '
echo '+-----+             Pipe                               |    '
echo '|ls -l| ------> fd 1 | fd 62 --------------------------+    '
echo '+-----+              |                                      '
echo ''
