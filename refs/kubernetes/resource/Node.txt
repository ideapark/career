# Node

- Address: hostname, internet IP, intranet IP.
- Condition: OutOfDisk, Ready, MemoryPressure, DiskPressure
- Capacity: CPU, Memory, Pod Counts.
- Info: Kernel Version, Container Version, OS Type

 Physical Machine or VM
+-----------------------------------+-------------------------------+
|            kubelet                |          docker/rkt           |
+-----------------------------------+-------------------------------+
|                                                                   |
|   10.10.10.1            10.10.10.2              10.10.10.3        |
| +------------+        +------------+          +------------+      |
| |  ##        |        | ##   @@    |          | ## @@ $$   |      |
| |  ##        |        | ##   @@    |          | ## @@ $$   |      |
| +------------+        +------------+          +-----+------+      |
|                                                     |             |
|  10.10.10.4                                         |             |
| +---------------+                                  Pod            |
| |               |                                                 |
| | ##  ##  @@ @@ |                                                 |
| | ##  ##  @@ @@<------ volume                                     |
| |      |        |                                                 |
| +------|--------+                                                 |
|     containerized app                                             |
|                                                                   |
+-------------------------------------------------------------------+
