#!/bin/bash

cat <<EOF
 $ diff -y <(ls -lF) <(ls -l)

 +------+             |
 |ls -lF| -----> fd 1 | fd 63 ---------------+
 +------+            Pipe                    |
                                             v
                              +----------------------------+
                              | diff /dev/fd/63 /dev/fd/62 |
                              +----------------------------+
                                                        ^
 +-----+             Pipe                               |
 |ls -l| ------> fd 1 | fd 62 --------------------------+
 +-----+              |

EOF

# temporary file descriptor
diff -y <(ls -lF) <(ls -l)
