# Getting started with etcd

[Origin Link](https://coreos.com/etcd/docs/latest/getting-started-with-etcd.html)

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

## Reading and writing to etcd

The HTTP-based API is easy to use. This guide will show both etcdctl and curl
examples.

From a Container Linux machine, set a key message with value Hello:

```bash
$ etcdctl set /message Hello
Hello
```

```bash
$ curl -X PUT http://127.0.0.1:2379/v2/keys/message -d value="Hello"
{"action":"set","node":{"key":"/message","value":"Hello","modifiedIndex":4,"createdIndex":4}}
```

Read the value of message back:

```bash
$ etcdctl get /message
Hello
```

```bash
$ curl http://127.0.0.1:2379/v2/keys/message
{"action":"get","node":{"key":"/message","value":"Hello","modifiedIndex":4,"createdIndex":4}}
```

If you followed a guide to set up more than one Container Linux machine, you can
SSH into another machine and can retrieve this same value.

To delete the key run:

```bash
etcdctl rm /message
```

```bash
$ curl -X DELETE http://127.0.0.1:2379/v2/keys/message
{"action":"delete","node":{"key":"/message","modifiedIndex":19,"createdIndex":4}}
```

## Reading and writing from inside a container

To read and write to etcd from within a container you must use the IP address
assigned to the docker0 interface on the Container Linux host. From the host,
run ip address show to find this address. It's normally 172.17.0.1.

To read from etcd, replace 127.0.0.1 when running curl in the container:

```bash
$ curl http://172.17.0.1:2379/v2/keys/
{"action":"get","node":{"key":"/","dir":true,"nodes":[{"key":"/coreos.com","dir":true,"modifiedIndex":4,"createdIndex":4}]}}
```

You can also fetch the docker0 IP programmatically:

```bash
ETCD_ENDPOINT="$(ifconfig docker0 | awk '/\<inet\>/ { print $2}'):2379"
```

## Proxy example

Let's pretend we're setting up a service that consists of a few containers that
are behind a proxy container. We can use etcd to announce these containers when
they start by creating a directory, having each container write a key within
that directory and have the proxy watch the entire directory. We're going to
skip creating the containers here but the docker guide is a good place to start
for that.

### Create the directory

Directories are automatically created when a key is placed inside. Let's call
our directory foo-service and create a key with information about a container:

```bash
$ etcdctl mkdir /foo-service
Cannot print key [/foo-service: Is a directory]
$ etcdctl set /foo-service/container1 localhost:1111
localhost:1111
```

```bash
$ curl -X PUT http://127.0.0.1:2379/v2/keys/foo-service/container1 -d value="localhost:1111"
{"action":"set","node":{"key":"/foo-service/container1","value":"localhost:1111","modifiedIndex":17,"createdIndex":17}}
```

Read the foo-service directory to see the entry:

```bash
$ etcdctl ls /foo-service
/foo-service/container1
```

```bash
$ curl http://127.0.0.1:2379/v2/keys/foo-service
{"action":"get","node":{"key":"/foo-service","dir":true,"nodes":[{"key":"/foo-service/container1","value":"localhost:1111","modifiedIndex":17,"createdIndex":17}],"modifiedIndex":17,"createdIndex":17}}
```

### Watching the directory

Now let's try watching the foo-service directory for changes, just like our
proxy would have to. First, open up another shell on a Container Linux host in
the cluster. In one window, start watching the directory and in the other
window, add another key container2 with the value localhost:2222 into the
directory. This command shouldn't output anything until the key has changed.
Many events can trigger a change, including a new, updated, deleted or expired
key.

```bash
$ etcdctl watch --recursive /foo-service
```

```bash
$ curl http://127.0.0.1:2379/v2/keys/foo-service?wait=true\&recursive=true
```

In the other window, let's pretend a new container has started and announced
itself to the proxy by running:

```bash
$ etcdctl set /foo-service/container2 localhost:2222
localhost:2222
```

```bash
$ curl -X PUT http://127.0.0.1:2379/v2/keys/foo-service/container2 -d value="localhost:2222"
{"action":"set","node":{"key":"/foo-service/container2","value":"localhost:2222","modifiedIndex":23,"createdIndex":23}}
```

In the first window, you should get the notification that the key has changed.
In a real application, this would trigger reconfiguration.

```bash
$ etcdctl watch --recursive /foo-service
localhost:2222
```

```bash
$ curl http://127.0.0.1:2379/v2/keys/foo-service?wait=true\&recursive=true
{"action":"set","node":{"key":"/foo-service/container2","value":"localhost:2222","modifiedIndex":23,"createdIndex":23}}
```

### Watching the directory and triggering an executable

Now let's try watching the foo-service directory for changes and - if there are
any - run the command. In one window, start watching the directory and in the
other window, add another key container3 with the value localhost:2222 into the
directory. This command shouldn't trigger anything until the key has changed.
The same events as in the previous example can trigger a change. The exec-watch
command expects etcdctl to run continuously (for watch command you can use
--forever option)

```bash
$ etcdctl exec-watch --recursive /foo-service -- sh -c 'echo "\"$ETCD_WATCH_KEY\" key was updated to \"$ETCD_WATCH_VALUE\" value by \"$ETCD_WATCH_ACTION\" action"'
```

In the other window, let's imagine a new container has started and announced
itself to the proxy by running:

```bash
$ etcdctl set /foo-service/container3 localhost:2222
localhost:2222
```

In the first window, you should get the notification that the key has changed.
We have used $ETCD_WATCH_* environment variables which were set by etcdctl.

```bash
$ etcdctl exec-watch --recursive /foo-service -- sh -c 'echo "\"$ETCD_WATCH_KEY\" key was updated to \"$ETCD_WATCH_VALUE\" value by \"$ETCD_WATCH_ACTION\" action"'
"/foo-service/container3" key was updated to "localhost:2222" value by "set" action
```

## Test and set

etcd can be used as a centralized coordination service and provides TestAndSet
functionality as the building block of such a service. You must provide the
previous value along with your new value. If the previous value matches the
current value the operation will succeed.

```bash
$ etcdctl set /message "Hi" --swap-with-value "Hello"
Hi
```

```bash
$ curl -X PUT http://127.0.0.1:2379/v2/keys/message?prevValue=Hello -d value=Hi
{"action":"compareAndSwap","node":{"key":"/message","value":"Hi","modifiedIndex":28,"createdIndex":27}}
```

## TTL

You can optionally set a TTL for a key to expire in a certain number of seconds.
Setting a TTL of 20 seconds:

```bash
$ etcdctl set /foo "Expiring Soon" --ttl 20
Expiring Soon
```

The curl response will contain an absolute timestamp of when the key will expire
and a relative number of seconds until that timestamp:

```bash
$ curl -X PUT http://127.0.0.1:2379/v2/keys/foo?ttl=20 -d value=bar
{"action":"set","node":{"key":"/foo","value":"bar","expiration":"2014-02-10T19:54:49.357382223Z","ttl":20,"modifiedIndex":31,"createdIndex":31}}
```

If you request a key that has already expired, you will be returned a 100:

```bash
$ etcdctl get /foo
Error: 100: Key not found (/foo) [32]
```

```bash
$ curl http://127.0.0.1:2379/v2/keys/foo
{"errorCode":100,"message":"Key not found","cause":"/foo","index":32}
```
