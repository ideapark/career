# Which Service Mesh Should I Use

## The Common Attributes of a Service Mesh

- Resiliency features (retries, timeouts, deadlines, etc)
- Cascading failure prevention (circuit breaking)
- Robust load balancing algorithms
- Control over request routing (useful for things like CI/CD release patterns)
- The ability to introduce and manage TLS termination between communication endpoints
- Rich sets of metrics to provide instrumentation at the service-to-service layer

## Product Comparisons

| Product | Features Maturity | Language | Kubernetes Support |
| ------- | ----------------- | -------- | ------------------ |
| linkerd | OK                | Scala    | Y                  |
| envoy   | +istio            | C++      | Y                  |
| istio   | +envoy            | Go       | Y                  |
| conduit | OK                | Rust/Go  | Y                  |

## Conclusion

istio+envoy
