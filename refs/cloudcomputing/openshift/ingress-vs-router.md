# Kubernetes ingress vs openshift route

| Feature                                      | Ingress on OpenShift | Route on OpenShift |
| -------------------------------------------- | -------------------- | ------------------ |
| Standard Kubernetes object                   | Yes                  | No                 |
| External access to services                  | Yes                  | Yes                |
| Persistent (sticky) sessions                 | Yes                  | Yes                |
| Load-balancing strategies (e.g. round robin) | Yes                  | Yes                |
| Rate-limit and throttling                    | Yes                  | Yes                |
| IP whitelisting                              | Yes                  | Yes                |
| TLS edge termination for improved security   | Yes                  | Yes                |
| TLS re-encryption for improved security      |                      | Yes                |
| TLS passthrough for improved security        |                      | Yes                |
| Multiple weighted backend (split traffic)    |                      | Yes                |
| Generated pattern-based hostnames            |                      | Yes                |
| Wildcard domains                             |                      | Yes                |
