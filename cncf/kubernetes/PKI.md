# PKI: Public Key Infrastructure

Kubernetes requires PKI for the following operations:

- Client certificates for the kubelet to authenticate to the API server
- Server certificate for the API server endpoint
- Client certificates for administrators of the cluster to authenticate to the API server
- Client certificates for the API server to talk to the kubelets
- Client certificate for the API server to talk to etcd
- Client certificate/kubeconfig for the controller manager to talk to the API server
- Client certificate/kubeconfig for the scheduler to talk to the API server
- Client and server certificates for the front-proxy

Default path to '/etc/kubernetes/pki'

## Single root CA

You can create a single root CA, controlled by an administrator. This root CA
can then create multiple intermediate CAs, and delegate all further creation to
Kubernetes itself.

| Path                   | Default CN                | description                    |
| ---                    | ---                       | ---                            |
| ca.crt,key             | kubernetes-ca             | Kubernetes general CA          |
| etcd/ca.crt,key        | etcd-ca                   | For all etcd-related functions |
| front-proxy-ca.crt,key | kubernetes-front-proxy-ca | For the front-end proxy        |

## All certificates

| Default CN                    | Parent CA                 | O (in Subject) | kind                   | hosts (SAN)                              |
| ---                           | ---                       | ---            | ---                    | ---                                      |
| kube-etcd                     | etcd-ca                   |                | server,client[etcdbug] | localhost,127.0.0.1                      |
| kube-etcd-peer                | etcd-ca                   |                | server,client          | <hostname>,<Host_IP>,localhost,127.0.0.1 |
| kube-etcd-healthcheck-client  | etcd-ca                   |                | client                 |                                          |
| kube-apiserver-etcd-client    | etcd-ca                   | system:masters | client                 |                                          |
| kube-apiserver                | kubernetes-ca             |                | server                 | <hostname>,<Host_IP>,<advertise_IP>,[1]  |
| kube-apiserver-kubelet-client | kubernetes-ca             | system:masters | client                 |                                          |
| front-proxy-client            | kubernetes-front-proxy-ca |                | client                 |                                          |

[1]: kubernetes, kubernetes.default, kubernetes.default.svc, kubernetes.default.svc.cluster, kubernetes.default.svc.cluster.local

| kind   | Key usage                                        |
| ---    | ---                                              |
| server | digital signature, key encipherment, server auth |
| client | digital signature, key encipherment, client auth |

## Certificate paths

| Default CN                   | recommend key path           | recommend cert path         | command        | key argument                 | cert argument                            |
| ---                          | ---                          | ---                         | ---            | ---                          | ---                                      |
| etcd-ca                      |                              | etcd/ca.crt                 | kube-apiserver |                              | --etcd-cafile                            |
| etcd-client                  | apiserver-etcd-client.crt    | apiserver-etcd-client.crt   | kube-apiserver | --etcd-certfile              | --etcd-keyfile                           |
| kubernetes-ca                |                              | ca.crt                      | kube-apiserver | --client-ca-file             |                                          |
| kube-apiserver               | apiserver.crt                | apiserver.key               | kube-apiserver | --tls-cert-file              | --tls-private-key                        |
| apiserver-kubelet-client     | apiserver-kubelet-client.crt |                             | kube-apiserver | --kubelet-client-certificate |                                          |
| front-proxy-client           | front-proxy-client.key       | front-proxy-client.crt      | kube-apiserver | --proxy-client-cert-file     | --proxy-client-key-file                  |
|                              |                              |                             |                |                              |                                          |
| etcd-ca                      |                              | etcd/ca.crt                 | etcd           |                              | --trusted-ca-file,--peer-trusted-ca-file |
| kube-etcd                    |                              | etcd/server.crt             | etcd           |                              | --cert-file                              |
| kube-etcd-peer               | etcd/peer.key                | etcd/peer.crt               | etcd           | --peer-key-file              | --peer-cert-file                         |
| etcd-ca                      |                              | etcd/ca.crt                 | etcdctl[2]     |                              | --cacert                                 |
| kube-etcd-healthcheck-client | etcd/healthcheck-client.key  | etcd/healthcheck-client.crt | etcdctl[2]     | --key                        | --cert                                   |

[2]: For a liveness probe, if self-hosted

## Configure certificates for user accounts

| filename                | credential name            | Default CN                     | O(in Subject)  |
| ---                     | ---                        | ---                            | ---            |
| admin.conf              | default-admin              | kubernetes-admin               | system:masters |
| kubelet.conf            | default-auth               | system:node:<nodename>         | system:nodes   |
| controller-manager.conf | default-controller-manager | system:kube-controller-manager |                |
| scheduler.conf          | default-manager            | system:kube-scheduler          |                |

These files are used as follows:

| filename                | command                 | comment                                                            |
| ---                     | ---                     | ---                                                                |
| admin.conf              | kubectl                 | Configure administrator user for the cluster                       |
| kubelet.conf            | kubelet                 | One required for each node in the cluster                          |
| controller-manager.conf | kube-controller-manager | Must be added to manifest in manifest/kube-controller-manager.yaml |
| scheduler.conf          | kube-scheduler          | Must be added to manifest in manifest/kube-scheduler.yaml          |
