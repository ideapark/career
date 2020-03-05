# Etcd

## Raft

- Time Sequence Required

```text
broadcastTime   <<   electionTimeout   <<    MTBF
 1.ms~10.ms           10.ms~500.ms        1.h~1.Month

broadcastTime : Network Latency + Disk Write
         MTBF : Mean Time Between Failures of Nodes
```

- Data Exchange

```text
                                                +--------+
                                                |Follower|<------+
                                                +--------+       |
                                              //                 |
                             3.1 Confirm:v=3 //                  |
                                            // 2.1 Copy:v=3      |
              4.1 Confirm:v=3              //                    |
+------+ <------------------------ +------+/                     |
|Client| ------------------------> |Leader|----------------------+ 4.2 Commit:v=3
+------+      1. Commit:v=3        +------+\                     |
                                           \\                    |
                                            \\                   |
                             3.1 Confirm:v=3 \\2.1 Copy:v=3      |
                                              \\                 |
                                                +--------+       |
                                                |Follower|<------+
                                                +--------+
```

## Etcd Server


- Architecture

```text
+-------------------------+
| +---------------------+ |
| |     HTTP LAYER      | |
| +---------------------+ |
|                         |
| +-------+ +-----------+ |
| |  RAFT | |           | |
| +-------+ | Replicate | |
| +-------+ | State     | |
| | Store | | Machine   | |
| +-------+ +-----------+ |
+-------------------------+
```

- Server Connection Topology

#.Connection = Cn^2

```text
+-------------+                 +-------------+
| ETCD-SERVER |<----------------| ETCD-SERVER |
+-------------|---------------->+-------------+
            /\\                   //\
              \\                 //
               \\               //
                \\             //
                 \\/         \//
                 +-------------+
                 | ETCD-SERVER |
                 +-------------+
```

## Cluster Initialization

- Static Configuration

- Etcd self-discovery

```bash
$ ETCD_DISCOVERY=$(curl https://discovery.etcd.io/new?size=3)
$ etcd --name etcdX
       --initial-advertise-peer-urls https://etcdX:2380
       --listen-peer-urls https://etcdX:2380
       --listen-client-urls https://etcdX:2379,https://localhost:2379
       --advertise-client-urls https://etcdX:2379
       --discovery $ETCD_DISCOVERY
```

- DNS self-discovery

```bash
$ dig +noall +answer SRV _etcd_server._tcp.example.com
_etcd_server._tcp.example.com. 300 IN   SRV  0 0 2380 etcd0.example.com
_etcd_server._tcp.example.com. 300 IN   SRV  0 0 2380 etcd1.example.com
_etcd_server._tcp.example.com. 300 IN   SRV  0 0 2380 etcd2.example.com

$ dig +noall +answer etcd0.example.com etcd1.example.com etcd2.example.com
etcd0.example.com. 300 IN  A    10.0.1.10
etcd1.example.com. 300 IN  A    10.0.1.20
etcd2.example.com. 300 IN  A    10.0.1.30

# X=[0,1,2]
$ etcd --name etcdX
       --initial-cluster-token etcd-cluster-##########
       --initial-cluster-state new
       --discovery-srv example.com
       --initial-advertise-peer-urls https://etcdX.example.com:2380
       --advertise-client-urls https://etcdX.example.com:2379
       --listen-client-urls https://etcdX.example.com:2379
       --listen-peer-urls https://etcdX.example.com:2380
```
