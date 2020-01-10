# Linux server tuning

- Open files

```bash
$ /proc/<pid>/limits
Max open files         30000
```

- Ephemeral ports

```text
32767 - 61000
```

- TIME_WAIT state

```text
net.ipv4.ip_local_port_range = 18000 65535
net.ipv4.netfilter.ip_conntrack_tcp_timeout_time_wait = 1
```

- Connection tracking

```text
net.netfilter.nf_conntrack_count
net.nf_conntrack_max
```

- Socket pending connections

Backlog of TCP connection waiting to be accepted by the application.

```text
net.core.somaxconn
```

- JVM thread count

Increase thread count limit by decreasing the stack size per thread (*-Xss*) or
by decreasing the memory allocated to the heap (*-Xms, -Xmx*).
