# Reserved IP Address

| Address block      |               Address range | Number of addresses | Scope           | Description                                                                                                            |
|--------------------|-----------------------------|---------------------|-----------------|------------------------------------------------------------------------------------------------------------------------|
| 0.0.0.0/8          |       0.0.0.0-0.255.255.255 |    16777216 (1<<24) | Software        | Current network (only valid as source address).                                                                        |
| 10.0.0.0/8         | 10.0.0.0-10.255.255.255.255 |            16777216 | Private network | Used for local communications within a private network                                                                 |
| 100.64.0.0/10      |  100.64.0.0-100.127.255.255 |             4194304 | Private network | Shared address space for communications between a service provider and its subscribers when using a carrier-grade NAT. |
| 127.0.0.0/8        |   127.0.0.0-127.255.255.255 |            16777216 | Host            | Used for loopback addresses to the local host.                                                                         |
| 169.254.0.0/16     | 169.254.0.0-169.254.255.255 |               65536 | Subnet          | Used for link-local addresses between two hosts on a single link when no IP address is otherwise specified,            |
|                    |                             |                     |                 | such as would have normally been retrieved from a DHCP server.                                                         |
| 172.16.0.0/12      |   172.16.0.0-172.31.255.255 |             1048576 | Private network | Used for local communications within a private network.                                                                |
| 192.0.0.0/24       |       192.0.0.0-192.0.0.255 |                 256 | Private network | IETF Protocal Assignments.                                                                                             |
| 192.0.2.0/24       |       192.0.2.0-192.0.2.255 |                 256 | Documentation   | Assigned as TEST-NET-1, documentation and examples.                                                                    |
| 192.88.99.0/24     |   192.88.99.0-192.88.99.255 |                 256 | Internet        | Reserved. Formerly used for IPv6 to IPv4 relay (included IPv6 address block 2002::/16).                                |
| 192.168.0.0/16     | 192.168.0.0-192.168.255.255 |               65536 | Private network | Used for local communications within a private network.                                                                |
| 198.18.0.0/15      |   198.18.0.0-198.19.255.255 |              131072 | Private network | Used for benchmark testing of inter-network communications between two separate subnets.                               |
| 198.51.100.0/24    | 198.51.100.0-198.51.100.255 |                 256 | Documentation   | Assigned as TEST-NET-2, documentation and examples.                                                                    |
| 203.0.113.0/24     |   203.0.113.0-203.0.113.255 |                 256 | Documentation   | Assigned as TEST-NET-3, documentation and examples.                                                                    |
| 224.0.0.0/4        |   224.0.0.0-239.255.255.255 |           268435456 | Internet        | In use for IP multicast. (Former Class D network).                                                                     |
| 240.0.0.0/4        |   240.0.0.0-255.255.255.254 |           268435456 | Internet        | Reserved for future use. (Former Class E network).                                                                     |
| 255.255.255.255/32 |             255.255.255.255 |                   1 | Subnet          | Reserved for the "limited broadcast" destination address.                                                              |
