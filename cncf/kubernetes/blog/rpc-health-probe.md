# gRPC Health Probe

- httpGet probe

Cannot be natively used with gRPC. You need to refactor your app to serve both
gRPC and HTTP/1.1 protocols (on different port numbers).

+---------------------+
| Container           |
|                     |
| +-----------------+ |
| | gRPC server app | |
| +-----------------+ |
|         ^           |
|         |           |
|    httpGet probe    |
|         |           |
+---------|-----------+
          |
     +---------+
     | kubelet |
     +---------+

- tcpSocket probe

Opening a socket to gRPC server is not meaningful, since it cannot reade the
response body.

+---------------------+
| Container           |
|                     |
| +-----------------+ |
| | gRPC server app | |
| +-----------------+ |
|         ^           |
|         |           |
|   tcpSocket probe   |
|         |           |
+---------|-----------+
          |
     +---------+
     | kubelet |
     +---------+

- exec probe

This invokes a program in a container's ecosystem periodically. In the case of
gRPC, this means you implement a health RPC yourself, then write and ship a
client tool with your container.

+----------------------+
| Container            |
|                      |
| +------------------+ |
| |  gRPC server app | |
| +------------------+ |
|          ^           |
|          |           |
|   custom grpc call   |
|          |           |
| +------------------+ | exec probe +---------+
| | gRPC test client |<|------------| kubelet |
| +------------------+ |            +---------+
+----------------------+

## grpc-health-probe

To standardize the "exec probe" approach, we need:

  1. a standard health check "protocol" that can be implemented in any gRPC
     server easily. (gRPC already has this protocol)

  2. a standard health check "tool" that can query the health protocol easily.

+----------------------+
| Container            |
|                      |
| +------------------+ |
| |  gRPC server app | |
| +------------------+ |
|          ^           |
|          |           |
|   standard grpc      |
|  health protocol     |
|          |           |
| +------------------+ | exec probe +---------+
| | grpc_health_probe|<|------------| kubelet |
| |   (standard CLI) | |            +---------+
| +------------------+ |
+----------------------+

By implementing the standard gRPC health check protocol, you can reuse the same
tool to probe all your gRPC servers.
