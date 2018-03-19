# Golang GC Algorithm Phases [Rick Hudson](https://talks.golang.org/2015/go-gc.pdf)

```
+--------------------------------------------------------------------------------------------------+
|                          |   |                                                                   |
|       Off                |   | GC disabled                                                       |
|                          |   | Pointer values are just memory writes: *slot = ptr                |
+--------------------------|---|-------------------------------------------------------------------+
|                    |     |STW|                                                                   |
|     Stack Scan     |     |---+ Collect pointers from globals and goroutine stacks                |
|                    |     |   | Stacks scanned at preemption points                               |
+--------------------|     |   |-------------------------------------------------------------------+
|                    |     |   |                                                                   |
|       Mark         |WB on|   | Mark objects and follow pointers until pointer queue is empty     |
|                    |     |   | Write barrier tracks pointer changes by mutator                   |
+--------------------|     |---|-------------------------------------------------------------------+
|                    |     |   |                                                                   |
|  Mark termination  |     |STW| Rescan globals/changed stacks, finish marking, shrink stacks, ... |
|                    |     |   | Literature contains non-STW algorithms: keeping it simple for now |
+--------------------------|---|-------------------------------------------------------------------+
|                          |   |                                                                   |
|      Sweep               |   | Reclaim unmarked objects as needed                                |
|                          |   | Adjust GC pacing for next cycle                                   |
+--------------------------|   |-------------------------------------------------------------------+
|                          |   |                                                                   |
|       Off                |   | Rinse and repeat                                                  |
|                          |   |                                                                   |
+--------------------------------------------------------------------------------------------------+
```
WB: write barrier STW: stop the world
