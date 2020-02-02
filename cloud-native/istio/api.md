# Istio API

*Gateways* configure physical listeners.

*VirtualServices* configure both virtual listeners (hostname matches are encoded
as separate listeners, and protocol processing is configured via listeners with
specific filters per protocol) and routes (HTTP/TLS match conditions, retry and
timeout configuration, etc.).

*ServiceEntrys* create clusters and populate their endpoints.

*DestinationRules* configure how to communicate with clusters (secrets,
load-balancing strategy, circuit breaking and connection pooling, etc.), and
create new clusters when they’re used to define subsets.


*Gateways* expose names.

*VirtualServices* configure and route names.

*DestinationRules* describe how to communicate with the workloads behind a name.

*ServiceEntrys* enable the creation of new names.
