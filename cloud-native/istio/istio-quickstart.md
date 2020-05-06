# Istio

1. connect
2. secure
3. control
4. observe

## Traffic Management

- Gateways

Configure physical listeners. `Gateways` expose names.

- VirtualServices

Configure both virtual listeners (hostname matches are encoded as separate
listeners, and protocol processing is configured via listeners with specific
filters per protocol) and routes (HTTP/TLS match conditions, retry and timeout
configuration, etc.). `VirtualServices` configure and route names.

- ServiceEntries

Create clusters and populate their endpoints. `ServiceEntries` enable the
creation of new names.

- DestinationRules

Configure how to communicate with clusters (secrets, load-balancing strategy,
circuit breaking and connection pooling, etc.), and create new clusters when
they’re used to define subsets. `DestinationRules` describe how to communicate
with the workloads behind a name.

- Sidecar

By default, Istio configures every Envoy proxy to accept traffic on all the
ports of its associated workload, and to reach every workload in the mesh when
forwarding traffic. You can use a sidecar configuration to do the following:

1. Fine-tune the set of ports and protocols that an Envoy proxy accepts.
2. Limit the set of services that the Envoy proxy can reach.

## Security (AAA)

- Authentication

Identity:

1. x509 SPIFFE (spiffe://cluster.local/ns/<default>/sa/<default>)
2. JWT: json web token (USE_ORIGIN)

Policy scope:

1. Mesh-Wide: `meshpolicy.authentication.istio.io`

A policy defined in the mesh-scope storage with no target selector section.
There can be at most one mesh-wide policy in the mesh.

2. Namespace-Wide: `policy.authentication.istio.io`

A policy defined in the namespace-scope storage with name default and no target
selector section. There can be at most one namespace-wide policy per namespace.

3. Service-Specific: `policy.authentication.istio.io`

A policy defined in the namespace-scope storage, with non-empty target selector
section. A namespace can have zero, one, or many service-specific policies.

- Authorization

1. AuthorizationPolicy

An authorization policy includes a selector and a list of rules. The selector
specifies the target that the policy applies to, while the rules specify who is
allowed to do what under which conditions. Specifically:

    target     refers to the selector section in the AuthorizationPolicy.
    who        refers to the from section in the rule of the AuthorizationPolicy.
    what       refers to the to section in the rule of the AuthorizationPolicy.
    conditions refers to the when section in the rule of the AuthorizationPolicy.

Each rule has the following standard fields:

    from: A list of sources.
    to:   A list of operations.
    when: A list of custom conditions.

## Policy Enforcement (istio-1.[3,4].x)

- Mixer Side

1. handler

Configuring a set of handlers, which determine the set of adapters that are
being used and how they operate. Providing a `statsd` adapter with the IP
address for a Statsd backend is an example of handler configuration.

2. instance

Configuring a set of instances, which describe how to map request attributes
into adapter inputs. Instances represent a chunk of data that one or more
adapters will operate on. For example, an operator may decide to generate
`requestcount` metric instances from attributes such as
`destination.service.host` and `response.code`.

3. rule

Configuring a set of rules, which describe when a particular adapter is called
and which instances it is given. Rules consist of a match expression and
actions. The match expression controls when to invoke an adapter, while the
actions determine the set of instances to give the adapter. For example, a rule
might send generated `requestcount` metric instances to a `statsd` adapter.

- Client Side

1. quotaspec

`QuotaSpec` defines quota name and amount that the client should request.

2. quotaspecbinding

`QuotaSpecBinding` conditionally associates QuotaSpec with one or more services.
