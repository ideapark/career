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
