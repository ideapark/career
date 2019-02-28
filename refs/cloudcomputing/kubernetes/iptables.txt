# IP Masquerade

## NAT (Network Address Translation)

is a method remapping one IP address to another by modifying either the source
and/or destination address information in the IP header. Typically performed by
a device doing IP routing.

## Masquerading

A form of NAT that is typically used to perform a many to one address
translation, where multiple source IP addresses are masked behind a single
address, which is typically the device doing IP routing. In Kubernetes this is
the Node's IP address.

## CIDR (Classless Inter-Domain Routing)

Based on the variable-length subnet masking, allows specifying arbitrary-length
prefixes. CIDR introduced a new method of representation for IP addresses, now
commonly known as CIDR notation, in which an address or routing prefix is
written with a suffix indicating the number of bits of the prefix, such as
192.168.2.0/24.

## Link Local

A link-local is a network address that is valid only for communications within
the network segment or the broadcast domain that the host is connected to.
Link-local addresses for IPv4 are defined in the address 169.254.0.0/16 in CIDR
notation.
