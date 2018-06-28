# Getting started with etcd

etcd is an open-source distributed key value store that provides shared
configuration and service discovery for Container Linux clusters. etcd runs on
each machine in a cluster and gracefully handles leader election during network
partitions and the loss of the current leader.

Application containers running on your cluster can read and write data into
etcd. Common examples are storing database connection details, cache settings,
feature flags, and more. This guide will walk you through a basic example of
reading and writing to etcd then proceed to other features like TTLs,
directories and watching a prefix. This guide is way more fun when you've got at
least one Container Linux machine up and running — try it on Amazon EC2 or
locally with Vagrant.

## Running etcd under Docker

In order to expose the etcd API to clients outside of the Docker host you'll
need use the host IP address when configuring etcd.

```bash
export HostIP="192.168.12.50"
```

The following docker run command will expose the etcd client API over ports 4001
and 2379, and expose the peer port over 2380.

This will run the latest release version of etcd. You can specify version if
needed (e.g. quay.io/coreos/etcd:v2.2.0).

```bash
docker run -d
           -v /usr/share/ca-certificates/:/etc/ssl/certs \
           -p 4001:4001 \
           -p 2380:2380 \
           -p 2379:2379 \
           --name etcd quay.io/coreos/etcd:v2.3.8 \
           -name etcd0 \
           -advertise-client-urls http://${HostIP}:2379,http://${HostIP}:4001 \
           -listen-client-urls http://0.0.0.0:2379,http://0.0.0.0:4001 \
           -initial-advertise-peer-urls http://${HostIP}:2380 \
           -listen-peer-urls http://0.0.0.0:2380 \
           -initial-cluster-token etcd-cluster-1 \
           -initial-cluster etcd0=http://${HostIP}:2380 \
           -initial-cluster-state new
```

Configure etcd clients to use the Docker host IP and one of the listening ports
from above.

```bash
etcdctl -C http://192.168.12.50:2379 member list

etcdctl -C http://192.168.12.50:4001 member list
```
