# Network packet

```text
Layer 7: the contents of your HTTP package like `GET /`
Layer 4: the port and other TCP/UDP information
Layer 3: the source IP and the destination IP
Layer 2: the MAC address this packet should go to
```

# Local networking

- arp table

```bash
$ ip neighbor
100.68.138.2   dev  wlp2s0   lladdr  44:00:4d:e2:54:cf  STALE
100.68.138.1   dev  wlp2s0   lladdr  00:00:5e:00:01:16  REACHABLE
192.168.100.2  dev  docker0  lladdr  02:42:c0:a8:64:02  STALE
```

MAC: 3c:97:ae:44:b3:7f

- If you're in the same local network, you can send a packet with any random IP
  address on it, and as long as the MAC address is right it'll get there.

- If you're in a different network, to send a packet to a computer, it has to
  have the IP address of that instance on it.

# Route table (cross networking)

```bash
$ ip route add 10.4.4.0/24 via 172.23.1.1 dev eth0
```

`ip route add` adds an entry to the route table on your computer. This route
table entry says "Linux, whenever you see a packet for 10.4.4.0/24", just send
it to the MAC address for `172.23.1.1`.
