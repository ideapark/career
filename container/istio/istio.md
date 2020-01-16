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

1. Pilot

The Pilot is responsible for managing the overall fleet—all of your
microservices’ sidecars running across your Kubernetes/OpenShift cluster. The
Istio Pilot ensures that each of the independent micro‐services, wrapped as
individual Linux containers and running inside their pods, has the current view
of the overall topology and an up-to-date “routing table.” Pilot provides
capabilities like service discovery as well as support for VirtualService. The
VirtualService is what gives you fine-grained request distribution, retries,
timeouts, etc.

2. Mixer

As the name implies, Mixer is the Istio service that brings things together.
Each of the distributed istio-proxies delivers its telemetry back to Mixer.
Furthermore, Mixer maintains the canonical model of the usage and access
policies for the overall suite of microservices. With Mixer, you can create
policies, apply rate-limiting rules, and even capture custom metrics. Mixer has
a pluggable backend architecture that is rapidly evolving with new plugins and
partners that are extending Mixer’s default capabilities in many new and
interesting ways.

3. Citadel

The Istio Citadel component, formerly known as Istio CA or Auth, is responsible
for certificate signing, certificate issuance, and revocation/rotation. Istio
issues X.509 certificates to all your microservices, allowing for mutual
Transport Layer Security (mTLS) between those services, encrypting all their
traffic transparently. It uses identity built into the underlying deployment
platform and builds that into the certificates. This identity allows you to
enforce policy.

## Up and Running

![istio](https://istio.io/docs/)

    $ istioctl kube-inject -f your-deployment.yaml

## Traffic Control

- DestinationRule

Establishes which pods make up a specific subset:

```yaml
apiVersion: networking.istio.io/v1alpha3
kind: DestinationRule
metadata:
  name: recommendation
  namespace: tutorial
spec:
  host: recommendation
  subsets:
  - name: version-v1
    labels:
      version: v1
  - name: version-v2
    labels:
      version: v2
```

- VirtualService

1. Directs traffic using a subset and a weighting factor:

```yaml
apiVersion: networking.istio.io/v1alpha3
kind: VirtualService
metadata:
  name: recommendation
  namespace: tutorial
spec:
  hosts:
  - recommendation
  http:
  - route:
    - destination:
        host: recommendation
        subset: version-v1
      weight: 90
    - destination:
        host: recommendation
        subset: version-v2
      weight: 10
```

2. This rule uses a request header–based matching clause that will match only if
   the request includes “Safari” as part of the user-agent header:

```yaml
apiVersion: networking.istio.io/v1alpha3
kind: VirtualService
metadata:
  name: recommendation
  namespace: tutorial
spec:
  hosts:
  - recommendation
  http:
  - route:
    - destination:
        host: recommendation
        subset: version-v1
    match:
    - headers:
        baggage-user-agent:
          regex: .*Safari.*
  - route:
    - destination:
        host: recommendation
        subset: version-v2
```
