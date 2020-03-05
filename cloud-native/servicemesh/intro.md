# Why We Need Service Mesh

A service mesh is a dedicated infrastructure layer for handling
service-to-service communication. It's responsible for the reliable delivery of
requests the complex topology of services that comprise a modern, cloud native
application.

In the cloud native model, a single application might consist of hundreds of
services; each service might have thousands of instances; and each of those
instances might be in a constantly-changing state as they are dynamically
scheduled by an orchestrator like Kubernetes. Not only is service communication
in this world incredibly complex, it's a pervasive and fundamental part of
runtime behavior. Managing it is vital to ensuring end-to-end performance and
reliability.

# Which Service Mesh Should I Use

- The Common Attributes of a Service Mesh

1. Resiliency features (retries, timeouts, deadlines, etc)
2. Cascading failure prevention (circuit breaking)
3. Robust load balancing algorithms
4. Control over request routing (useful for things like CI/CD release patterns)
5. The ability to introduce and manage TLS termination between communication endpoints
6. Rich sets of metrics to provide instrumentation at the service-to-service layer

- Product Comparisons

| Product | Features Maturity | Language | Kubernetes Support |
| ------- | ----------------- | -------- | ------------------ |
| linkerd | OK                | Scala    | Y                  |
| envoy   | +istio            | C++      | Y                  |
| istio   | +envoy            | Go       | Y                  |
| conduit | OK                | Rust/Go  | Y                  |

- Conclusion

istio+envoy wins

# Istio

Istio lets you connect, secure, control, and observe services. istio's diverse
feature set lets you successfully, and efficiently, run a distributed
microservice architecture, and provides a uniform way to secure, connect, and
monitor microservice.

## Core Features

### Traffic management

- circuit breaker
- timeout
- retries
- A/B testing
- Canary rollouts
- Staged rollouts
- Percentage-based traffic splits

### Security

Service communications are secured by default

### Observability

Istio's robust tracing, monitoring, and logging give you deep insights into your
service mesh deployment. Gain a real understanding of how service performance
impacts things upstream and downstream with Istio's monitoring feature, while
its custom dashboards provide visibility into the performance of all your
services and let you see how that performance is affecting your other processes.

### Platform support

- Service deployment on Kubernetes
- Services registered with Consul
- Services running on individual virtual machines

### Integration and customization

The policy enforcement component of Istio can be extended and customized to
integrate with existing solutions for ACLs, logging, monitoring, quotas,
auditing, and more.

## Architecture

- data plane

Composed of a set of intelligent proxies (Envoy) deployed as sidecars. These
proxies mediate and control all network communication between microservices
along with Mixer, a general-purpose policy and telemetry hub.

- control plane

Manages and configures the proxies to route traffic. Additionally, the control
plane configures Mixers to enforce policies and collect telemetry.

```text
+----------------+                     +----------------+
| +------------+ |                     | +------------+ |
| |  Service A | |                     | |  Service B | |
| +------------+ | HTTP/1.1, HTTP/2,   | +------------+ |
|       |        | gRPC or TCP --      |        |       |
|       |        | with or without     |        |       |
| +------------+ | mTLS                | +------------+ |
| |   Proxy    |-|---------------------|>|    Proxy   | |
| +------------+ |                     | +------------+ |
+----------------+                     +----------------+
                 \                     /
                  \                   /
                   \  Policy checks  /
        |    /      \   telemetry   /       \    |
 Config |   /        \             /         \   | TLS certs to
 data to|  /          \           /           \  | proxies
 proxies| /            +---------+             \ |
        |/                                      \|
 +---------+    +------------------------+   +-----------+
 |  Pilot  |    |         Mixer          |   |  Citadel  |
 +---------+    +------------------------+   +-----------+
     |                                              |
     |               Control Plane API              |
     +----------------------------------------------+
```
