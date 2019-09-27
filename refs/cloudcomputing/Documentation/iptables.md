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
