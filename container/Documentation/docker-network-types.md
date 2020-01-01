# Docker Network Types

- Host Networking

The container shares the same IP address and network namespace as that of the
host. Services running inside of this container have the same network
capabilities as services running directly on the host.

- Bridge Networking

The container runs in a private network internal to the host. Communication is
open to other containers in the same network. Communication with services
outside of the host goes through network address translation (NAT) before
exiting the host. (This is the default mode of networking when the `--net`
option isn't specified)

- Custom bridge network

This is the same as Bridge Networking but uses a bridge explicitly created for
this (and other) containers. An example of how to use this would be a container
that runs on an exclusive "database" bridge network. Another container can have
an interface on the default bridge and the database bridge, enabling it to
communicate with both networks.

- Container-defined Networking

A container can share the address and network configuration of another
container. This type enables process isolation between containers, where each
container runs one service but where services can still communicate with one
another on the `localhost` address.

- No Networking

This option disables all networking for the container.
