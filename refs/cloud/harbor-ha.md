# Harbor High Availability

## HA

- Compute HA (DONE)
- Storage HA (DONE)
- Network HA (TODO)

## Solution

```text
                      LB
                       |
                       | replica:3
                   +-------+
                   | Nginx | Nginx Service
                   +-------+
                    /     \
                   /       \
     replica:3    /         \      replica:3
   +--------------+         +-----------------+
   | Admin server |         | Docker Registry |
   |--------------|         |-----------------|
   |  UI          |         | Shared Storage  | NFS/GlusterFS/CephFS
   |--------------|         +-----------------+
   |  API         |                | replica:1
   |--------------|       +--------------------+
   |  Auth        |-------| Replcation Service |
   +--------------+       +--------------------+
         \                      /
          \                    /
           \                  /
            \    replica:3   /
            +----------------+
            |     MySQL      |
            |----------------|
            | Galera Cluster | http://galeracluster.com
            +----------------+
```
