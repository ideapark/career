# Istio

## Service Mesh

Service mesh is the connective tissue between your services that adds additional
capabilities like *traffic control*, *service discovery*, *load balancing*,
*resilience*, *observability*, *security*, and so on. A service mesh allows
applications to offload these capabilities from application-level libraries
and allows developers to focus on differentiating business logic.

## Istio

![istio](istio.png)

- Data Plane

1. Service proxy

The service proxy acts as an intermediary or interceptor that can add
capabilities like automatic retries, circuit breaker, service discovery,
security, and more. The default service proxy for Istio is based on Envoy proxy.
It provides features like load balancing for HTTP1.1, HTTP2, and gRPC. It has
the ability to collect request-level metrics, trace spans, provide for service
discovery, inject faults, and much more. You might notice that some of the
capabilities of Istio overlap with Envoy. This fact is simply explained as Istio
uses Envoy for its implementation of these capabilities.

2. Sidecar

With Istio, a second Linux container called “istio-proxy” (aka the Envoy service
proxy) is manually or automatically injected into the pod that houses your
application or microservice. This sidecar is responsible for intercepting all
inbound (ingress) and outbound (egress) network traffic from your business logic
container, which means new policies can be applied that reroute the traffic (in
or out), perhaps apply policies such as access control lists (ACLs) or rate
limits, also snatch monitoring and tracing data (Mixer), and even introduce a
little chaos such as network delays or HTTP errors.

- Control Plane
