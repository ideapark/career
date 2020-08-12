# L4 vs L7 Load Balancing / Traffic Management

|             | L4                                  | L7                                                                                       |
| ---         | ---                                 | ---                                                                                      |
| Load        | Basic load balancing                | Advanced load balancing                                                                  |
| Blancing    | 1. Based on IP address & port only  | 1. Based on URL - images, text, video                                                    |
|             |                                     | 2. Based on client information - browser, OS, device, language                           |
|             | HTTP(S) blind                       | Takes advantage of the HTTP(S) packet info. Designed for apps of today & tomorrow        |
|             | No Content (payload) rewrite &      | Supports content rewriting: Apps with hard-coded URLs, mergers & acquisitions,           |
|             | switching: Inability to change      | publishing internal URLs, misconfigured apps, respond to malicious traffic.              |
|             | anything on the wire                | Can parse the payload and apply changes; allows making smarter content optimization      |
|             |                                     | and security decisions like app firewalling along with doing proxy.                      |
| ---         | ---                                 | ---                                                                                      |
| Session     | Very limited:                       | Advanced session persistence for better user experience                                  |
| Persistence | Only based on client IP address     | Can use cookies - identify users to provide persistent experience                        |
|             |                                     | Better experience for stateful applications                                              |
| ---         | ---                                 | ---                                                                                      |
| Resource    | Health checking limited to Ping and | Advanced customizable health checks                                                      |
| Monitoring  | TCP handshake only                  | Application-level visibility for better observability and load balancing decisions       |
|             |                                     | Enables circuit-breaking capabilities                                                    |
| ---         | ---                                 | ---                                                                                      |
| App         | Very limited due to just IP address | Advanced protection due to deep packet inspection                                        |
| Security    | and port visibility                 | Examples: web application firewall, L7 DoS protection, application stack vulnerabilities |
|             | Lacks deep packet inspection        | based on signature analysis, anomaly detection                                           |
