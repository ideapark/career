# Network packet

Layer 7: the contents of your HTTP package like `GET /`
Layer 4: the port and other TCP/UDP information
Layer 3: the source IP and the destination IP
Layer 2: the MAC address this packet should go to

# Local networking

- arp table

```
# arp -n
Address                  HWtype  HWaddress           Flags Mask            Iface
172.17.1.161             ether   ee:ff:ff:ff:ff:ff   C                     eth0
172.17.1.191             ether   ee:ff:ff:ff:ff:ff   C                     eth0
10.130.0.157             ether   0a:58:0a:82:00:9d   C                     tun0
10.128.2.54              ether   0a:58:0a:80:02:36   C                     tun0
172.17.1.152             ether   ee:ff:ff:ff:ff:ff   C                     eth0
```

MAC: 3c:97:ae:44:b3:7f

- If you're in the same local network, you can send a packet with any random IP
  address on it, and as long as the MAC address is right it'll get there.

- If you;re in a different network, to send a packet to a computer, it has to
  have the IP address of that instance on it.

# Route table (cross networking)

```
ip route add 10.4.4.0/24 via 172.23.1.1 dev eth0
```

`ip route add ` adds an entry to the route table on your computer. This route
table entry says "Linux, whenever you see a packet for 10.4.4.0/24", just send
it to the MAC address for `172.23.1.1`.
