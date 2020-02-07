# Container Orchestration Capabilities And Focus VS Service-Level Needs

- Application Layer Networking

```text
+-------------------------------------------------------+
| Additional Key Capabilities                           |
|                                                       |
| 1. Simple Application Health & Performance Monitoring |
| 2. Application Deployments                            |
| 3. Application Secrets                                |
+-------------------------------------------------------+
```

- Service Layer Networking (e.g, Istio ServiceMesh)

```text
+------------------------------------------+
| Missing Service-Level needs:             |
|                                          |
| 1. Circuit breaking                      |
| 2. L7 granular traffic routing           |
| 2.1. HTTP Redirects                      |
| 2.2. CORS Handling                       |
| 3. Chaos Testing                         |
| 4. Canary deploys                        |
| 5. Timeouts, retries, budgets, deadlines |
| 6. Per-request routing                   |
| 7. Backpressure                          |
| 8. Transport security (encryption)       |
| 9. Identity and access control           |
| 10. Quota management                     |
| 11. Protocol translation (REST, GRPC)    |
| 12. Policy                               |
| 13. Service performance monitoring       |
+------------------------------------------+
```

- Lower Layer Networking (e.g, Kubernetes Networking)

```text
+----------------------------------------------+
| Core Capabilities                            |
|                                              |
| 1. Cluster Management                        |
| 1.1 Host Discovery                           |
| 1.2 Host Health Monitoring                   |
| 2. Scheduling                                |
| 3. Orchestrator Updates and Host maintenance |
| 4. Service Discovery                         |
| 5. Networking and Load-Balancing             |
| 6. Stateful services                         |
| 7. Multi-tenant, multi-region                |
+----------------------------------------------+
```
