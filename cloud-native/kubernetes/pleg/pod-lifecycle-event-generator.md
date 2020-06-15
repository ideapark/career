# PLEG: pod lifecycle event generator

```text

  Pod spec  |
  changes   |                     ...........
            v                    / worker-1 .                              +-----------+
      +-----------+             /           .         create/kill          |           |
      |  kubelet  |------------|-- worker-2 .----------------------------->|           |
      +-----------+             \           .                              | container |
            ^                    \ worker-N .                              |  runtime  |
 pod events |                     ...........                              |           |
            |                                                              |           |
    +--------------------------------------+                               |           |
    | pod lifecycle event generator (PLEG) |------------------------------>|           |
    +--------------------------------------+       examine containers      +-----------+
                       ^
                       |
           +--------------------------+
           | upstream container state |
           |     event generator      |
           +--------------------------+
```
