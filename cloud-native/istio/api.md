# Istio API Objects

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
