# Istio API Objects

## Traffic Management

- Gateways

Configure physical listeners. *Gateways* expose names.

- VirtualServices

Configure both virtual listeners (hostname matches are encoded as separate
listeners, and protocol processing is configured via listeners with specific
filters per protocol) and routes (HTTP/TLS match conditions, retry and timeout
configuration, etc.). *VirtualServices* configure and route names.

- ServiceEntrys

Create clusters and populate their endpoints. *ServiceEntrys* enable the
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

1. X.509 SPIFF (spiff://cluster.local/ns/default/sa/default)
2. JWT (USE_ORIGIN)

Policy enforcement:

1. MeshPolicy (mesh wide)
2. Policy (namespace wide, service wide)

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
