# ip Command Cheat Sheet

## IP QUERIES

### addr

Display IP Addresses and property information (abbreviation of address)

```
# Show information for all addresses
$ ip addr

# Display information only for device em1
$ ip addr show dev em1
```

### link

Manage and display the state of all network interfaces

```
# Show information for all interfaces
$ ip link

# Display information only for device em1
$ ip link show dev em1

# Display interface statistics
$ ip -s link
```

### route

Display and alter  the routing table

```
# List all of the route entries in the kernel
$ ip route
```

### maddr

Manage and display multicast IP addresses

```
# Display multicast information for all devices
$ ip maddr

# Display multicast information for device em1
$ ip maddr show dev em1
```

### neigh

Show neighbour objects; also known as the ARP table for IPv4

```
# Display neighbour objects
$ ip neigh

# Show the ARP cache for device em1
$ ip neigh show dev em1
```

### help

Display a list of commands and arguments for each subcommand

```
# Display ip commands and arguments
$ ip help

# Display address commands and arguments
$ ip addr help

# Display link commands and arguments
$ ip link help

# Display heighbour commands and arguments
$ ip neigh help
```

## MULTICAST ADDRESSING

### maddr add

Add a static link-layer multicast address

```
# Add multicast address 33:33:00:00:00:01 to em1
$ ip maddr add 33:33:00:00:00:01 dev em1
```

### maddr del

Delete a multicast address

```
# Delete address 33:33:00:00:00:01 from em1
$ ip maddr del 33:33:00:00:00:01 dev em1
```

## MODIFYING ADDRESS  AND LINK PROPERTIES

### addr add

Add an address

```
# Add address 192.168.1.1 with netmask 24 to device em1
$ ip addr add 192.168.1.1/24 dev em1
```

### addr del

Delete an address

```
# Remove address 192.168.1.1/24 from device em1
$ ip addr del 192.168.1.1/24 dev em1
```

### link set

Alter the status of the interface

```
# Bring em1 online
$ ip link set em1 up

# Bring em1 offline
$ ip link set em1 down

# Set the MTU on em1 to 9000
$ ip link set em1 mtu 9000

# Enable promiscuous mode for em1
$ ip link set em1 promisc on
```

## ADJUSTING AND VIEWING ROUTES

## route add

Add an entry to the routing table

```
# Add a default route (for all addresses) via the local gateway
# 192.168.1.1 that can be reached on device em1
$ ip route add default via 192.168.1.1 dev em1

# Add a route to 192.168.1.0/24 via the gateway at 192.168.1.1
$ ip route add 192.168.1.0/24 via 192.168.1.1

# Add a route to 192.168.1.0/24 that can be reached on device em1
$ ip route add 192.168.1.0/24 dev em1
```

### route delete

Delete a routing table entry

```
# Delete the route for 192.168.1.0/24 via the gateway at 192.168.1.1
$ ip route delete 192.168.1.0/24 via 192.168.1.1
```

### route replace

Replace, or add if not defined, a route

```
# Replace the defined  route for 192.168.1.0/24 to use device em1
$ ip route replace 192.168.1.0/24 dev em1
```

### route get

Display the route an address will take

```
# Display the route taken for IP 192.168.1.5
$ ip route get 192.168.1.5
```

## MANAGING THE ARP TABLE

### neigh add

Add an entry to the ARP table

```
# Add address 192.168.1.1 with MAC 1:2:3:4:5:6 to em1
$ ip neigh add 192.168.1.1 lladdr 1:2:3:4:5:6 dev em1
```

### neigh del

Invalidate an entry

```
# Invalidate the entry for 192.168.1.1 on em1
$ ip neigh del 192.168.1.1 dev em1
```

### neigh replace

Replace, or adds if not defined, an entry to the ARP table

```
# Replace the entry for address 192.168.1.1 to use MAC 1:2:3:4:5:6 on em1
$ ip neigh replace 192.168.1.1 lladdr 1:2:3:4:5:6 dev em1
```

## USEFUL NETWORKING COMMANDS (NOT NECESSARILY PROVIDED FROM IPROUTE)

### arping

Send ARP request to a enighbour host

```
# Send ARP request to 192.168.1.1 via interface eth0
$ arp -I eth0 192.168.1.1

# Check for duplicate MAC addresses at 192.168.1.1 on eth0
$ arp -D -I eth0 192.168.1.1
```

### ethtool

Query or control network driver and hardware settings

```
# Display ring buffer for eth0
$ ethtool -g eth0

# Display driver information for eth0
$ ethtool -i eth0

# Identify eth0 by sight, typically by causing LEDs to blink on the network port
$ ethtool -p eth0

# Display network and driver statistics for eht0
$ ethtool -S eth0
```

### ss

Display socket statistics. The below options can be combined

```
# Show all sockets (listening and non-listening)
$ ss -a

# Show detailed socket information
$ ss -e

# Show timer information
$ ss -o

# Do not resolve addresses
$ ss -n

# Show process using the socket
$ ss -p
```

## COMPARING NET-TOOLS VS. IPROUTE PACKAGE COMMANDS

| NET-TOOLS COMMANDS                                        | IPROUTE COMMANDS                                     |
|-----------------------------------------------------------|------------------------------------------------------|
| arp -a                                                    | ip neigh                                             |
| arp -v                                                    | ip -s neigh                                          |
| arp -s 192.168.1.1 1:2:3:4:5:6                            | ip neigh add 192.168.1.1 lladdr 1:2:3:4:5:6 dev eth1 |
| arp -i eth1 -d 192.168.1.1                                | ip neigh del 192.168.1.1 dev eth1                    |
| ifconfig -a                                               | ip addr                                              |
| ifconfig eth0 down                                        | ip link set eth0 down                                |
| ifconfig eth0 up                                          | ip link set eth0 up                                  |
| ifconfig eth0 192.168.1.1                                 | ip addr add 192.168.1.1/24 dev eth0                  |
| ifconfig eth0 netmask 255.255.255.0                       | ip addr add 192.168.1.1/24 dev eth0                  |
| ifconfig eth0 mtu 9000                                    | ip link set eth0 mtu 9000                            |
| ifconfig eth0:0 192.168.1.2                               | ip addr add 192.168.1.2/24 dev eth0                  |
| netstat                                                   | ss                                                   |
| netstat -neopa                                            | ss -neopa                                            |
| netstat -g                                                | ip maddr                                             |
| route                                                     | ip route                                             |
| route add -net 192.168.1.0 netmask 255.255.255.0 dev eth0 | ip route add 192.168.1.0/24 dev eth0                 |
| route add default gw 192.168.1.1                          | ip route add default via 192.168.1.1                 |
