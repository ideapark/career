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
discovery, inject faults, and much more.

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

- [istio](https://istio.io/docs/)
- [istio profile](profile.md)

```bash
# mannual injection
$ istioctl kube-inject -f kube-deployment.yaml

# automatic injection
$ kubectl label namespace my-namespace istio-injection=enabled
```

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

3. Traffic mirror (Dark launch):

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
    mirror:
      host: recommendation
      subset: version-v2
```

- Egress

Istio by default blocks all outbound (outside of the cluster) traffic unless you
specifically and explicitly create rules to allow traffic out.

```yaml
apiVersion: networking.istio.io/v1alpha3
kind: ServiceEntry
metadata:
  name: httpbin-egress-rule
  namespace: tutorial
spec:
  hosts:
  - now.httpbin.org
  ports:
  - name: http-80
    number: 80
    protocol: http
```

```text
$ kubectl get serviceentry -n tutorial
SERVICE-ENTRY NAME    HOSTS             PORTS    NAMESPACE  AGE
httpbin-egress-rule   now.httpbin.org   http/80  tutorial   5m
```

## Service Resiliency

Istio comes with many capabilities for implementing resilience within
applications, but just as we noted earlier, the actual enforcement of these
capabilities happens in the sidecar. This means that the resilience features
listed here are not targeted toward any specific programming language/runtime;
they’re applicable regardless of library or framework you choose to write your
service:

1. Client-side load balancing

Istio augments Kubernetes out-of-the-box load balancing.

2. Timeout

Wait only N seconds for a response and then give up.

3. Retry

If one pod returns an error (e.g., 503), retry for another pod.

4. Simple circuit breaker

Instead of overwhelming the degraded service, open the circuit and reject
further requests.

5. Pool ejection

This provides auto removal of error-prone pods from the load- balancing pool.

### Load Balancing

1. ROUND_ROBIN

This algorithm evenly distributes the load, in order, across the endpoints in
the load-balancing pool.

2. RANDOM

This evenly distributes the load across the endpoints in the load-balancing pool
but without any order.

```yaml
apiVersion: networking.istio.io/v1alpha3
kind: DestinationRule
metadata:
  name: recommendation
  namespace: tutorial
spec:
  host: recommendation
  trafficPolicy:
    loadBalancer:
      simple: RANDOM
```

3. LEAST_CONN

This algorithm picks two random hosts from the load-balancing pool and
determines which host has fewer outstanding requests (of the two) and sends to
that endpoint. This is an implementa‐ tion of weighted least request load
balancing.

### Timeout

Waiting is not a good solution if there is a customer on the other end of the
request. Waiting also uses resources, causes other systems to potentially wait,
and is usully a significant contributor to cascading failures. Your network
traffic should always have timeouts in place, and you can use Istio service mesh
to do this.

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
    timeout: 1.000s
```

### Retry

The network is not reliable you might experience transient, intermittent errors.
This can be even more pronounced with distributed microservices rapidly
deploying several times a week or even a day. The service or pod might have gone
down only briefly. With Istio’s retry capability, you can make a few more
attempts before having to truly deal with the error, potentially falling back to
default logic.

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
    retries:
      attempts: 3
      perTryTimeout: 2s
```

### Circuit Breaker

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
    trafficPolicy:
      connectionPool:
        http:
          http1MaxPendingRequests: 1
          maxRequestsPerConnection: 1
        tcp:
          maxConnections: 1
      outlierDetection:
        baseEjectionTime: 120.000s
        consecutiveErrors: 1
        interval: 1.000s
        maxEjectionPercent: 100
```

### Pool Ejection

Identifying badly behaving cluster hosts and not sending any more traffic to
them for a cool-off period (essentially kicking the bad-behaving pod out of the
load-balancing pool).

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
    trafficPolicy:
      connectionPool:
        http: {}
        tcp: {}
      loadBalancer:
        simple: RANDOM
      outlierDetection:
        baseEjectionTime: 15.000s
        consecutiveErrors: 1
        interval: 5.000s
        maxEjectionPercent: 100
  - name: version-v2
    labels:
      version: v2
    trafficPolicy:
      connectionPool:
        http: {}
        tcp: {}
      loadBalancer:
        simple: RANDOM
      outlierDetection:
        baseEjectionTime: 15.000s
        consecutiveErrors: 1
        interval: 5.000s
        maxEjectionPercent: 100
```

### Combination: Circuit Breaker + Pool Ejection + Retry

1. Circuit breaker

to avoid multiple concurrent requests to an instance

2. Pool ejection

to remove failing instances from the pool of responding instances

3. Retries

to forward the request to another instance just in case you get an open circuit
breaker or pool ejection

## Chaos Testing

- HTTP Errors

```yaml
---
apiVersion: networking.istio.io/v1alpha3
kind: DestinationRule
metadata:
  name: recommendation
  namespace: tutorial
spec:
  host: recommendation
  subsets:
  - name: app-recommendation
    labels:
      app: recommendation
---
apiVersion: networking.istio.io/v1alpha3
kind: VirtualService
metadata:
  name: recommendation
  namespace: tutorial
spec:
  hosts:
  - recommendation
  http:
  - fault:
      abort:
        httpStatus: 503
        percent: 50
      route:
      - destination:
          host: recommendation
          subset: app-recommendation
```

- Delays

The most insidious of possible distributed computing faults is not a “dead”
service but a service that is responding slowly, potentially causing a cascading
failure in your network of services.

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
  - fault:
      delay:
        fixedDelay: 7.000s
        percent: 50
    route:
    - destination:
        host: recommendation
        subset: app-recommendation
```

## Observability

### Tracing

- OpenTracing Headers

```text
x-request-id
x-b3-traceid
x-b3-spanid
x-b3-parentspanid
x-b3-sampled
x-b3-flags
x-ot-span-context
```

### Metrics

- Promethues + Grafana

1. Latency
2. Traffic
3. Errors
4. Saturation

### Service Graph

- Kiali

## Security

### mutual Transport Layer Security (mTLS)

Enabling mTLS in Istio uses the combination of Policy and DestinationRule
objects.

This applies to all services in the tutorial namespace. You can also optionally
set a "mode" of *PERMISSIVE* versus *STRICT*. which allows for both mTLS and
non-mTLS traffic, useful for scenarios where the sidecar, istio-proxy, has not
yet been applied to all of your services.

```yaml
---
apiVersion: authentication.istio.io/v1alpha3
kind: Policy
metadata:
  name: default
  namespace: tutorial
spec:
  peers:
  - mtls: {}
---
apiVersion: networking.istio.io/v1alpha3
kind: DestinationRule
metadata:
  name: default
  namespace: tutorial
spec:
  host: "*.tutorial.svc.cluster.local"
  trafficPolicy:
    tls:
      mode: ISTIO_MUTUAL
```

Now that you have enabled mTLS, you need to leverage a gateway to achieve
end-to-end encryption. To set up the Istio Gateway for the customer service,
create the Gate way and its supporting VirtualService objects.

```yaml
---
apiVersion: networking.istio.io/v1alpha3
kind: Gateway
metadata:
  name: customer-gateway
  namespace: tutorial
spec:
  selector:
    istio: ingressgateway  # use istio default controller
  servers:
  - port:
      number: 80
      name: http
      protocol: HTTP
    hosts:
    - "*"
---
apiVersion: networking.istio.io/v1alpha3
kind: VirtualService
metadata:
  name: customer
  namespace: tutorial
spec:
  hosts:
  - "*"
  gateways:
  - customer-gateway
  http:
  - route:
    - destination:
        host: customer
        port:
          number: 8080
    match:
    - uri:
        exact: /
```

### Access Control with Mixer Policy

Istio’s Mixer Policy service allows you to construct a series of rules that
ensure the various microservices that make up your application follow an
approved invocation path.

### Role-Based Access Control (RBAC)

```yaml
apiVersion: "rbac.istio.io/v1alpha1"
kind: RbacConfig
metadata:
  name: default
spec:
  mode: ON_WITH_INCLUSION
  inclusion:
    namespaces: ["tutorial"]
```

- OFF

Istio authorization is disabled.

- ON

Istio authorization is enabled for all services in the mesh.

- ON_WITH_INCLUSION

Enabled only for services and namespaces specified in the inclusion field.

- ON_WITH_EXCLUSION

Enabled for all services in the mesh except the services and namespaces
specified in the exclusion field.

```yaml
---
apiVersion: rbac.istio.io/v1alpha1
kind: ServiceRole
metadata:
  name: service-viewer
  namespace: tutorial
spec:
  rules:
  - services: ["*"]
    methods: ["GET"]
    constraints:
    - key: "destination.labels[app]"
      values: ["customer", "recommendation", "preference"]
---
apiVersion: rbac.istio.io/v1alpha1
kind: ServiceRoleBinding
metadata:
  name: bind-service-viewer
  namespace: tutorial
spec:
  subjects:
  - user: "*"
  roleRef:
    kind: ServiceRole
    name: "service-viewer"
```
