# Harbor High Availability

## Theory

### Stateless service

| SERVICE     |
| ----------- |
| Adminserver |
| UI          |
| Registry    |
| Logs        |
| Jobservice  |
| Clair       |
| Proxy       |

- Redundant
- Load Balance

### Stateful service

| SERVICE                      |
| ---------------------------- |
| Harbor database (MariaDB)    |
| Clair database (PostgresSQL) |
| Notary database (MariaDB)    |
| Redis                        |

Depend on the high availability implementation for each application, such as
MySQL Galera Cluster.

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

## HA Completed

- Compute HA (DONE)
- Storage HA (DONE)
- Network HA (TODO)
