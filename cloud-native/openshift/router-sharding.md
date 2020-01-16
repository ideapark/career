# Router Sharding and DNS

Router sharding using namespace and route labels.

```text
                                   +-------+
                +------------------|       |------------------+
                |                  +-------+                  |
                |                  Interface                  |
                |                      |                      |
                |                      |                      |
                V                      V                      v
         +-------------+       +-----------------+     +---------------+
         | ROUTER 1    |       | ROUTER 2        |     | ROUTER 3      |
         |             |       |                 |     |               |
         | LABEL 1     |       | LABEL 2         |     | LABEL 3       |
         |             |       | LABEL 3         |     |               |
         +-------------+       +-----------------+     +---------------+
                |                      |                      |
                |             +--------|--------|-----------+ |
                |             |                 |           | |
                |             |                 |           | |
                v             v                 v           v v
       +-------------+   +-------------+  +-------------+  +-------------+
       | NAMESPACE 1 |   | NAMESPACE 2 |  | NAMESPACE 3 |  | NAMESPACE 4 |
       |             |   |             |  |             |  |             |
       | Service 1   |   | Service 1   |  | Service 1   |  | Service 1   |
       | Service 2   |   | Service 2   |  |             |  |             |
       |             |   |             |  |             |  |             |
       | LABEL 1     |   | LABEL 2     |  | LABEL 2     |  | LABEL 3     |
       +-------------+   +-------------+  +-------------+  +-------------+
```
