# kube-proxy intermittent connection reset

## What caused the connection reset

                                                Kube-Proxy
                                  (1)              +-+             (2)
                         +-------------------+     | |     +-------------------+
                         |src: 10.0.0.2:34567|     | |     |src: 10.0.0.2:34567|
+------------+ --------> |dst: 192.168.0.2:80| --> | | --> |dst: 10.0.1.2:80   | -------> +------------+
|            |           +-------------------+     | |     +-------------------+          |            |
|            |                                     | |                                    |            |
| Client Pod |                                     | |                                    | Server Pod |
| (10.0.0.2) |                                     | |                                    | (10.0.1.2) |
|            |                    (4)              | |   INVALID!  (3)                    |            |
|            |       +-----------------------+     | |     +-------------------+          |            |
+------------+ <---- |src: 10.0.1.2:80 (OOPS)|     | |     |src: 10.0.1.2:80   | <------- +------------+
      |              |dst: 10.0.0.2:34567    | <-- | | <-- |dst: 10.0.0.2:34567|                ^
      |              +-----------------------+     | |     +-------------------+                |
      |                                            +-+                                          |
      |                                       (5)                                               |
      +--------->--------------------> +-------------------+ -------------->------------>-------+
                                       |flag: RST          |
                                       |src: 10.0.0.2:34567|
                                       |dst: 10.0.0.1:80   |
                                       +-------------------+

## How to fixup

- Make conntrack more liberal on packets, and don’t mark the packets as INVALID.
  In Linux, you can do this by echo 1 >
  /proc/sys/net/ipv4/netfilter/ip_conntrack_tcp_be_liberal.

- Specifically add an iptables rule to drop the packets that are marked as
  INVALID, so it won’t reach to client pod and cause harm.
