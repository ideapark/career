# Cloud Native Trail Map

## Containerization

  1. Commonly done with Docker containers
  2. Any size application and dependencies (even PDP-11 code running on an
     emulator) can be containerized
  3. Over time, you should aspire towards splitting suitable applications and
     writing future functionality as microservices

## CI/CD

  1. Setup Continuous Integration/Conginuous Delivery (CI/CD) so that changes to
     your source code automatically result in a new container being built,
     tested, and deployed to staging and eventually, perhaps, to production
  2. Setup automated rollouts, roll backs and testing

## Orchestration & Application Definition

  1. Kubernetes is the market-leading orchestraction solution
  2. You should select a Certified Kubernetes Distribution, Hosted Platform, or
     Intaller: cncf.io/ck
  3. Helm Charts help you define, install, and upgrade even the most complex
     Kubernetes application

## Observability and Analysis

  1. Pick solutions for monitoring, logging and tracing
  2. Consider CNCF projects Prometheus for monitoring, Fluentd for logging and
     Jaeger for Tracing
  3. For tracing, look for an OpenTracing-compatible implementation like Jaeger

## Service Proxy, Discovery, & Mesh

  1. CoreDNS is a fast and flexible tool that is useful for service discovery
  2. Envoy and Linkerd each enable service mesh architectures
  3. They offer health checking, routing, and load balancing

## Networking

  1. to enable more flexible networking, use a CNI-compliant network project
     like Calico, Flannel, or Weave Net

## Distributed Database & Storage

  1. When you need more resiliency and scalability than you can get from a
     single database, Vitess is a good option for running MySQL at scale through
     sharding. Rook is a storage orchestrator that integrates a diverse set of
     storage solutions into Kubernetes. Serving as the "brain" of Kubernetes,
     etcd provides a reliable way to store data across a cluster of machines.

## Streaming & Messaging

  1. When you need higher performance than JSON-REST, consider using gRPC
     framework. NATS is a multi-modal messaging system that includes
     request/reply, pub/sub and load balanced queues

## Container Registry & Runtime

  1. Harobr is a registry that stores, signs, and scans content. You can use
     alternative container runtimes. The most common, all of which are
     OCI-compliant, are containerd, rkt and CRI-O.

## Software Distribution

  1. If you need to do secure software distribution, evaluate Notary, and
     implementation of The Update Framework.
