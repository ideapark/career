# OpenShift SDN

## Packet Flow

Suppose you have two containers, A and B, where the peer virtual Ethernet device
for container A's eth0 is named vethA and the peer for container B's eth0 is
named vethB.

Now suppose first that container A is on the local host and container B is also
on the local host. Then the flow of packets from container A to container B is
as follows:

```text
eth0 (in A's netns) --> vethA --> br0 --> vethB --> eth0 (in B's netns)
```

Next, suppose instead that container A is on the local host and container B is
on a remote host on the cluster network. Then the flow of packets from container
A to container B is as follows:

```text
eth0 (in A's netns) --> vethA --> br0 --> vxlan0 --> network --> vxlan0 --> br0 --> vethB --> eth0 (in B's netns)
```

Finally, if container A connects to an external host, the traffic looks like:

```text
eth0 (in A's netns) --> vethA --> br0 --> tun0 --> (NAT) --> eth0 (physical device) --> internet
```

## Access Diagram

```
+---------------+                     +------------------+                     +------------+
|Machine outside|    External Net     |Node with external|     Cluster Net     |            |
| the cluster   |-------------------->|      access      |-------------------->|Cluster Node|
+---------------+                     +------------------+                     +------------+
                                       \                /                        \
                             Public IP  \              / Node IP          Node IP \
                             Access      \            /  Address          Address  \
                                          \          /                              \
                                           \        /                                \  Pod IP
                                            \      /                                  \ Address
                                        +-------------+  Pod IP                  +-------------+
                                        |"Router" pod | Address                  | Cluster Pod |
                                        |(in the node)|(local to the cluster)    |(in the node)|
                                        +-------------+                          +-------------+
```
