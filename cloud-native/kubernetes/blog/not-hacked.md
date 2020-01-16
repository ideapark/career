# Not to Get Hacked

## The control plane

- TLS every where

TLS should be enabled for every component that supports it to prevent traffic
sniffing, verify the identity of the server, and (for mutual TLS) verify the
identity of the client.

Kubernetes component connection protocol

![Component Connection Protocol](kubernetes-control-plane.png)

Node TLS Bootstrap

![Node TLS Bootstrap](node-tls-bootstrap.png)

- Enable RBAC with least privilege, disable ABAC, and monitor logs

Role-based access control provides fine-grained policy management for user
access to resources, such as access to namespaces.

- Use third party auth for API Server

Centralising authentication and authorisation across an organisation (aka Single
Sign On) helps onboarding, offboarding, and consistent permissions for users.

- Separate and firewall your etcd cluster

etcd stores information on state and secrets, and is a critical Kubernetes
component - it should be protected differently from the rest of your cluster.

- Rotate encryption keys

A security best practice is to regularly rotate encryption keys and
certificates, in order to limit the "blast radius" of a key compromise.

## Workloads

- Use linux security features and PodSecurityPolicies

The Linux kernel has a number of overlapping security extensions (capabilities,
SELinux, AppArmor, seccomp-bpf) that can be configured to provide least
privilege to applications.

- Statically analyse YAML

Where PodSecurityPolicies deny access to the API server, static analysis can
also be used in the development workflow to model an organisation's compliance
requirements or risk appetite.

- Run containers as a non-root user

Containers that run as root frequently have far more permissions than their
workload requires which, in case of compromise, could help an attacker further
their attack.

- Use network policies

By default, Kubernetes networking allows all pod to pod traffic; this can be
restricted using a Network Policy.

- Scan images and run IDS

Web servers present an attack surface to the network they're attached to:
scanning an image's installed files ensures the absence of known vulnerabilities
that an attacker could exploit to gain remote access to the container. An IDS
(Intrusion Detection System) detects them if they do.

## The future

- Run a service mesh

A service mesh is a web of encrypted persistent connections, made between high
performance "sidecar" proxy servers like Envoy and Linkerd. It adds traffic
management, monitoring, and policy - all without microservice changes.
