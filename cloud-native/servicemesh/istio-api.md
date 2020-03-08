# Istio API Objects

## Traffic Management

- Gateways

Configure physical listeners. *Gateways* expose names.

- VirtualServices

Configure both virtual listeners (hostname matches are encoded as separate
listeners, and protocol processing is configured via listeners with specific
filters per protocol) and routes (HTTP/TLS match conditions, retry and timeout
configuration, etc.). *VirtualServices* configure and route names.

- ServiceEntries

Create clusters and populate their endpoints. *ServiceEntries* enable the
creation of new names.

- DestinationRules

Configure how to communicate with clusters (secrets, load-balancing strategy,
circuit breaking and connection pooling, etc.), and create new clusters when
they’re used to define subsets. *DestinationRules* describe how to communicate
with the workloads behind a name.

- Sidecar

By default, Istio configures every Envoy proxy to accept traffic on all the
ports of its associated workload, and to reach every workload in the mesh when
forwarding traffic. You can use a sidecar configuration to do the following:

1. Fine-tune the set of ports and protocols that an Envoy proxy accepts.
2. Limit the set of services that the Envoy proxy can reach.

## Security

- Authentication

Identity:

1. x509 SPIFFE (spiffe://cluster.local/ns/default/sa/default)
2. JWT: json web token (USE_ORIGIN)

Policy scope:

1. Mesh-wide: *meshpolicy.authentication.istio.io*

A policy defined in the mesh-scope storage with no target selector section.
There can be at most one mesh-wide policy in the mesh.

2. Namespace-wide: *policy.authentication.istio.io*

A policy defined in the namespace-scope storage with name default and no target
selector section. There can be at most one namespace-wide policy per namespace.

3. Service-specific: *policy.authentication.istio.io*

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

## Policy

- Handler
- Instance
- Rule