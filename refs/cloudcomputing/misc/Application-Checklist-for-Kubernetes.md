# Application Checklist for Kubernetes

These are the areas that need attention before running your cluster in
production.

|                      | What is it                                  | Why you need it                              | Options                           |
| ---                  | ---                                         | ---                                          | ---                               |
| Readiness Check      | Endpoints for Kubernetes to monitor         | Allows Kubernetes to restart or stop traffic | Read: Resilient apps with         |
|                      | your application lifecycle.                 | to a pod.                                    | Liveness and Readiness            |
|                      |                                             | Readiness failure is transient and tells     | probes.                           |
|                      |                                             | Kubernetes to route traffic elsewhere        |                                   |
|                      |                                             | Readiness failure is useful for startup and  |                                   |
|                      |                                             | load management                              |                                   |
|                      |                                             |                                              |                                   |
| Liveness check       | Endpoints for Kubernetes to monitor         | Liveness failure is for telling Kubernetes   | Read: Resilient apps with         |
|                      | your application lifecycle.                 | to restart the pod.                          | Liveness and Readiness            |
|                      |                                             |                                              | probes.                           |
|                      |                                             |                                              |                                   |
| Metric               | Code and libraries used in your code to     | Allows measuring operation of application    | Prometheus, New Relic,            |
| instrumentation      | expose metrics.                             | and enables many more advanced use           | Datadog and others.               |
|                      |                                             | cases.                                       | Read: Monitoring Kubernetes       |
|                      |                                             |                                              | with Prometheus.                  |
|                      |                                             |                                              |                                   |
| Dashboards           | View of metrics.                            | You need to make sense out of the data.      | Grafana                           |
|                      |                                             |                                              | Weave Cloud                       |
|                      |                                             |                                              |                                   |
| Playbooks/Runbooks   | Rich guides for your engineers on how-      | Nobody is at their sharpest at 03:00 AM.     | Confluence                        |
|                      | to operate the system and fault find        |                                              | Markdown files                    |
|                      | when things go wrong.                       | Knowledge deteriorates over time             | Weave Cloud Notebooks             |
|                      |                                             |                                              |                                   |
| Limits and requests  | Explicit resource allocation for pods.      | Allows Kubernetes to make good               | Read: Kubernetes Pod              |
|                      |                                             | scheduling decisions.                        | Resource Limitations and          |
|                      |                                             |                                              | Quality of Service.               |
|                      |                                             |                                              |                                   |
| Labels and           | Metadata held by Kubernetes.                | Makes workload management easier and         | Read: Labels and Selectors        |
| annotations          |                                             | allows other tools to work with standard     | in Kubernetes.                    |
|                      |                                             | Kubernetes definitions.                      |                                   |
|                      |                                             |                                              |                                   |
| Alerts               | Automated notifications on defined          | You need to know when your service           | Prometheus & Alertmanager.        |
|                      |                                             | degrades.                                    | Read: Labels in Prometheus        |
|                      |                                             |                                              | alerts: think twice before        |
|                      |                                             |                                              | using them.                       |
|                      |                                             |                                              |                                   |
| Structured logging   | Output logs in a machine readable           | Trace what went wrong when something         | ELK stack (Elasticsearch,         |
| output               | format to facilitate searching & indexing.  | does.                                        | Logstash and Kibana).             |
|                      |                                             |                                              | Many commercial offerings.        |
|                      |                                             |                                              |                                   |
| Tracing              | Instrumentation to send request             | Sometimes the only way of figuring out       | Zipkin, Lightstep, Appdash,       |
| instrumentation      | processing details to a collection          | where latency is coming from                 | Tracer, Jaeger                    |
|                      | service.                                    |                                              |                                   |
|                      |                                             |                                              |                                   |
| Graceful shutdowns   | Applications respond to SIGTERM             | This is how Kubernetes will tell your        | Read: 10 tips for Building        |
|                      | correctly.                                  | application to end.                          | and Managing Containers           |
|                      |                                             |                                              |                                   |
| Graceful             | Applications don’t assume                   | Avoid headaches that come with a service     | Read: 10 tips for Building        |
| dependency (w.       | dependencies are available. Wait for        | order requirement.                           | and Managing Containers           |
| Readiness check)     | other services before reporting ready.      |                                              |                                   |
|                      |                                             |                                              |                                   |
| Configmaps           | Define a configuration file for your        | Easy to reconfigure an app without           | Read: Best Practices for          |
|                      | application in Kubernetes using configmaps. | rebuilding, allows config to be versioned.   | Designing and Building Containers |
|                      |                                             |                                              | for Kubernetes                    |
|                      |                                             |                                              |                                   |
| Label the docker     | Makes tracing image to code trivial.        | Locked down runtime context                  | Read: Introduction to             |
| images with the code |                                             |                                              | Kubernetes Security               |
| commit SHA.          |                                             |                                              |                                   |
|                      |                                             |                                              |                                   |
| Locked down          | Use deliberately secure configuration       | Reduces attack surface, makes privileges     | Read: Continuous Security         |
| runtime context      | for application runtime context.            | explicit.                                    | for GitOps                        |
