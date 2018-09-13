# Job

Job is used for short lived one-off tasks, and ensures one or more Pods finished
successfully.

## Job Controller

```text
                       +-----------+
                       | Scheduler |
                       +-----------+    +----+
                           |  | pod    /|Node|
                       pod |  |binding/ +----+
                           |  |      /
                           |  |     /
     +------+   job    +----------+/    +----+
     |client|--------->|API Server|-----|Node|
     +------+          +----------+\    +----+
                           |  |     \
                           |  |      \
                       job |  | pod   \ +----+
                           |  |        \|Node|
                       +----------+     +--+---+
                       |    Job   |        |Pod|
                       |Controller|        +---+
                       +----------+
```
