# the flow of packets through the chains in various tables


```text
+---------+                         PREROUTING                                                   INPUT                +---------+
|         |     +--------------------------------------------------+                +----------------------------+    |         |
|         |     |   +-----+   +----------+   +--------+   +-----+  |                |   +--------+   +--------+  |    |         |
|         |-----|-->| raw |-->|connection|-->| mangle |-->| nat |--|----------------|-->| mangle |-->| filter |--|--->|         |
|         |     |   +-----+   | tracking |   +--------+   +-----+  |                |   +--------+   +--------+  |    |         |
|         |     |             +----------+                   |     |                +----------------------------+    |         |
|         |     +--------------------------------------------------+                                                  |         |
|         |                                                  |                                                        |         |
| Network |                                                  |                                                        |  Local  |
|interface|                                             +----------+                                                  | Process |
|         |                                             |    v     |                                                  |         |
|         |                                             | +------+ |                                                  |         |
|         |                                             | |mangle| | FORWARD                                          |         |
|         |                                             | +------+ |                                                  |         |
|         |                                             |    |     |                                                  |         |
|         |                                             |    v     |                                                  |         |
|         |                                             | +------+ |                                                  |         |
|         |                                +------------|-|filter| |                                                  |         |
|         |                                |            | +------+ |                                                  |         |
|         |                                |            +----------+                                                  |         |
|         |                                v                                                                          |         |
|         |                +---------------------------+    +------------------------------------------------------+  |         |
|         |                | +-----+   +--------+      |    | +------+   +-----+   +------+   +----------+   +---+ |  |         |
|         |                | | nat |<--| mangle |      |<---| |filter|<--| nat |<--|mangle|<--|connection|<--|raw| |--|         |
|         |                | +-----+   +--------+      |    | +------+   +-----+   +------+   | tracking |   +---+ |  |         |
|         |                +---------------------------+    +------------------------------------------------------+  |         |
|         |                         POSTROUTING                                      OUTPUT                           |         |
+---------+                                                                                                           +---------+
```

```bash
# See `filter` table rules without DNS resolving
iptables -L -n --line-numbers

# Module `tcp`, `conntrack`, `recent`
iptables -A INPUT \
         -p tcp \
         -m tcp --dport 22 \
         -m conntrack --ctstate NEW \
         -m recent --set --name SSHLIMIT --rsource

# Create chain `ssh-rules`
iptables -N ssh-rules
iptables -A ssh-rules -s 18.130.0.0/16 -j ACCEPT
iptables -A ssh-rules -s 18.11.0.0/16  -j ACCEPT
iptables -A ssh-rules -j DROP

# Refer to chain `ssh-rules`
iptables -A INPUT -p tcp -m tcp --dport 22 -j ssh-rules

# Delete chain `ssh-rules`
iptables -X ssh-rules
```

- Example firewall configuration

```bash
*filter
:INPUT DROP [0:0]
:FORWARD DROP [0:0]
:OUTPUT DROP [0:0]

# allow local loopback connections
-A INPUT -i lo -j ACCEPT

# drop INVALID connections
-A INPUT   -m state --state INVALID -j DROP
-A OUTPUT  -m state --state INVALID -j DROP
-A FORWARD -m state --state INVALID -j DROP

# allow all established and related
-A INPUT  -m state --state ESTABLISHED,RELATED -j ACCEPT
-A OUTPUT -m state --state ESTABLISHED,RELATED -j ACCEPT

# allow connections to my ISP's DNS servers
-A OUTPUT -d 2.3.4.10 -m state --state NEW -p udp --dport 53 -o eth0 -j ACCEPT
-A OUTPUT -d 2.3.4.11 -m state --state NEW -p udp --dport 53 -o eth0 -j ACCEPT

# allow outgoing connections to web servers
-A OUTPUT -d 0/0 -m state --state NEW -p tcp --dport http  -o eth0 -j ACCEPT
-A OUTPUT        -m state --state NEW -p tcp --dport https -o eth0 -j ACCEPT

# allow outgoing mail connections to my ISP's SMTP and POP3 server only
-A OUTPUT -d 2.3.4.5 -m state --state NEW -p tcp --dport smtp -o eth0 -j ACCEPT
-A OUTPUT -d 2.3.4.5 -m state --state NEW -p tcp --dport pop3 -o eth0 -j ACCEPT

# log all other attempted out going connections
-A OUTPUT -o eth0 -j LOG

# default is to DROP out-going connections

COMMIT
```

- SNAT (source NAT) example

```bash
*filter
:INPUT DROP [0:0]
:FORWARD DROP [0:0]
:OUTPUT DROP [0:0]

# allow local loopback connections
-A INPUT -i lo -j ACCEPT

# drop INVALID connections
-A INPUT   -m state --state INVALID -j DROP
-A OUTPUT  -m state --state INVALID -j DROP
-A FORWARD -m state --state INVALID -j DROP

# allow all established and related
-A INPUT   -m state --state ESTABLISHED,RELATED -j ACCEPT
-A OUTPUT  -m state --state ESTABLISHED,RELATED -j ACCEPT
-A FORWARD -m state --state ESTABLISHED,RELATED -j ACCEPT

# allow connections to my ISP's DNS servers
-A OUTPUT  -d 2.3.4.10 -m state --state NEW -p udp --dport 53 -o eth0 -j ACCEPT
-A OUTPUT  -d 2.3.4.11 -m state --state NEW -p udp --dport 53 -o eth0 -j ACCEPT
-A FORWARD -d 2.3.4.10 -m state --state NEW -p udp --dport 53 -i eth1 -o eth0 -j ACCEPT
-A FORWARD -d 2.3.4.11 -m state --state NEW -p udp --dport 53 -i eth1 -o eth0 -j ACCEPT

# allow outgoing connections to web servers
-A OUTPUT  -d 0/0 -m state --state NEW -p tcp -m multiport --dport http,https -o eth0 -j ACCEPT
-A FORWARD -d 0/0 -m state --state NEW -p tcp -m multiport --dport http,https -o eth0 -i eth1 -j ACCEPT

# allow outgoing mail connections to my ISP's SMTP and POP3 server only
-A OUTPUT  -d mail.my-isp.com -m state --state NEW -p tcp -m multiport --dport smtp,pop3 -o eth0 -j ACCEPT
-A FORWARD -d mail.my-isp.com -m state --state NEW -p tcp -m multiport --dport smtp,pop3 -o eth0 -j ACCEPT

# log all other attempted out going connections
-A OUTPUT -o eth0 -j LOG
-A FORWARD -j LOG

# default is to DROP out-going connections
COMMIT

*nat

# set up IP forwarding and nat
-A POSTROUTING -o eth0 -j MASQUERADE

COMMIT
```

- DNAT (destination NAT) example

```bash
*nat

# set up IP forwarding and nat
-A POSTROUTING -o eth0 -j SNAT --to 1.2.3.4
-A PREROUTING -i eth0 -p tcp -d 1.2.3.4 --dport 80 -j DNAT --to 192.168.0.3:8080

COMMIT
```

- The Most Commonly Used Targets

| Target     | Desciption                                                                                                                                              | Most Common Options                                                                                                             |
|------------|---------------------------------------------------------------------------------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------------------|
| ACCEPT     | iptables stops further processing.                                                                                                                      | N/A                                                                                                                             |
|            | The packet is handed over to the end application or the operating system for processing                                                                 |                                                                                                                                 |
|            |                                                                                                                                                         |                                                                                                                                 |
| DROP       | iptables stops further processing.                                                                                                                      | N/A                                                                                                                             |
|            | The packet is blocked                                                                                                                                   |                                                                                                                                 |
|            |                                                                                                                                                         |                                                                                                                                 |
| LOG        | The packet information is sent to the syslog daemon for logging                                                                                         | --log-prefix "string"                                                                                                           |
|            | iptables continues processing with the next rule in the table                                                                                           | Tells iptables to prefix all log messages with a user defined string. Frequently used to tell why the logged packet was dropped |
|            | As you can't log and drop at the same time, it is common to have two similar rules in sequence. The first will log the packet, the second will drop it. |                                                                                                                                 |
|            |                                                                                                                                                         |                                                                                                                                 |
| REJECT     | Works like the DROP target, but will also return an error message to the host sending the packet that the packet was blocked                            | --reject-with qualifier                                                                                                         |
|            |                                                                                                                                                         | The qualifier tells what type of reject message is returned. Qualifiers include:                                                |
|            |                                                                                                                                                         | icmp-port-unreachable (default)                                                                                                 |
|            |                                                                                                                                                         | icmp-net-unreachable                                                                                                            |
|            |                                                                                                                                                         | icmp-host-unreachable                                                                                                           |
|            |                                                                                                                                                         | icmp-proto-unreachable                                                                                                          |
|            |                                                                                                                                                         | icmp-net-prohibited                                                                                                             |
|            |                                                                                                                                                         | icmp-host-prohibited                                                                                                            |
|            |                                                                                                                                                         | tcp-reset                                                                                                                       |
|            |                                                                                                                                                         | echo-reply                                                                                                                      |
|            |                                                                                                                                                         |                                                                                                                                 |
| DNAT       | Used to do destination network address translation. ie. rewriting the destination IP address of the packet                                              | --to-destination ipaddress                                                                                                      |
|            |                                                                                                                                                         | Tells iptables what the destination IP address should be                                                                        |
|            |                                                                                                                                                         |                                                                                                                                 |
| SNAT       | Used to do source network address translation rewriting the source IP address of the packet                                                             | --to-source <address>[-<address>][:<port>-<port>]                                                                               |
|            | The source IP address is user defined                                                                                                                   | Specifies the source IP address and ports to be used by SNAT.                                                                   |
|            |                                                                                                                                                         |                                                                                                                                 |
| MASQUERADE | Used to do Source Network Address Translation.                                                                                                          | [--to-ports <port>[-<port>]]                                                                                                    |
|            | By default the source IP address is the same as that used by the firewall's interface                                                                   | Specifies the range of source ports to which the original source port can be mapped.                                            |
