# What is Production Ready?

“Your offering is production ready when it exceeds customer expectations in a
way that allows for business growth.” --Carter Morgan, Developer Advocate,
Google.

Cluster production readiness is somewhat dependant on your use case and can be
about making tradeoffs. Although a cluster can be production ready when it’s
good enough to serve traffic, many agree that there are a minimum set of
requirements you need before you can safely declare your cluster ready for
commercial traffic.

When creating a reliable production set-up, the following areas are important.
Some of these topics will be more important than others, depending on your
specific use case.

## Keep security vulnerabilities and attack surfaces to a minimum.

Ensure that the applications you are running are secure and that the data you
are storing, whether it's your own or your clients, is secured against attack.
In addition to this, be aware of security breaches within your own development
environments. And because Kubernetes is a rapidly growing open source project,
you’ll also need to be on top of the updates and patches so that they can be
applied in a timely manner.

## Maximize portability and scalability by fine tuning cluster performance.

Running and managing applications anywhere is why Kubernetes is the number one
orchestrator, as is its ability to self-heal nodes, autoscale infrastructure and
adapt to your expanding business. Most want all of the benefits of self-healing
and scalability without taking a performance hit.

## Implement secure CICD pipelines for continuous delivery.

With your infrastructure in place, an automated continuous deployment and
delivery pipeline allows your development team to maximize their velocity and
improve productivity through increased release frequency and repeatable
deployments.

## Apply observability as a deployment catalyst.

Observability is not only about being able to monitor your system, but it’s also
about having a high-level view into your running services so that you can make
decisions before you deploy. To achieve true observability you need the
processes and tools in place to act on that monitoring through timely incident
alerts.

## Create a disaster recovery plan.

Ensure that you have high availability which means that if you have a failure
your cluster can recover automatically. In the case of complete cluster meltdown
with the adoption of GitOps best practices

# The Production Ready Checklist for Clusters

These are the areas that need attention before running your cluster in
production.

|                | What is it                                      | Why you need it                                   | Options                 |
| ---            | ---                                             | ---                                               | ---                     |
| Build Pipeline | Tests, integrates, builds and deposits          | Ensures a bug free artefact before deployment.    | CircleCI                |
|                | container artefact to registry.                 |                                                   | Travis                  |
|                | Artefacts should be tagged with Git commit      |                                                   | Jenkins                 |
|                | SHA to verify provenance                        |                                                   | and others.             |
|                |                                                 |                                                   |                         |
| Deployment     | Takes the build artefacts, and delivers them    | More secure way of doing deployment. Can add      | Weave Cloud             |
| Pipeline       | to the cluster. This is where GitOps occurs.    | approval checkpoints if needed.                   | Flux                    |
|                |                                                 |                                                   |                         |
| Image          | Stores build artefacts.                         | Keeps versioned artefacts available.              | Roll your own           |
| Registry       | Needs credentials for CI to push and for        |                                                   | Commercial:             |
|                | cluster to pull images.                         |                                                   | DockerHub               |
|                |                                                 |                                                   | JFrog                   |
|                |                                                 |                                                   | GCP Registry            |
|                |                                                 |                                                   |                         |
| Monitoring     | Collects and stores metrics.                    | Understands your running system. Alerts when      | OSS:                    |
| Infrastructure |                                                 | something goes wrong.                             | Prometheus              |
|                |                                                 |                                                   | Cortex,                 |
|                |                                                 |                                                   | Thanos                  |
|                |                                                 |                                                   | Commercial:             |
|                |                                                 |                                                   | Datadog                 |
|                |                                                 |                                                   | Grafana Cloud           |
|                |                                                 |                                                   | Weave Cloud             |
|                |                                                 |                                                   |                         |
| Shared Storage | Stores the persistent state of your application | No one ever has a stateless app.                  | Many.                   |
|                | beyond the pod's lifetime. Seen by your app as  |                                                   | Depends on              |
|                | a directory and can be read-only.               |                                                   | the platform.           |
|                |                                                 |                                                   |                         |
| Secrets        | How your applications access secret             | Secrets are required to access external services. | Bitnami sealed secrets. |
| management     | credentials across your application and to      |                                                   | Hashicorp Vault.        |
|                | and from the cluster.                           |                                                   |                         |
|                |                                                 |                                                   |                         |
| Ingress        | Provides a common routing point for all         | Easier to manage authentication and logging.      | AWS ELB                 |
| controller     | inbound traffic.                                |                                                   | NGINX                   |
|                |                                                 |                                                   | Kong                    |
|                |                                                 |                                                   | Traefik                 |
|                |                                                 |                                                   | HAProxy                 |
|                |                                                 |                                                   | Istio                   |
|                |                                                 |                                                   |                         |
| API Gateway    | Creates a single point for incoming             | Routes at HTTP level. Enables common and          | Ambassador (Envoy)      |
|                | requests and is a higher level ingress          | centralized tooling for tracing, logging,         | Roll your own           |
|                | controller that can replace an ingress          | authentication.                                   |                         |
|                | controller.                                     |                                                   |                         |
|                |                                                 |                                                   |                         |
| Service Mesh   | Provides an additional layer on top of          | Enables complex use cases like Progressive        | Linkerd                 |
|                | Kubernetes to manage routing.                   | Delivery. Adds inter-service TLS, Load balancing, | Istio                   |
|                |                                                 | service discovery, monitoring and tracing.        |                         |
|                |                                                 |                                                   |                         |
| Service        | Enables easy dependencies on services           | Simplifies deploying applications.                | Kubernetes’ service     |
| catalogue /    | and service discovery for your team             |                                                   | catalog API             |
| Broker         |                                                 |                                                   |                         |
|                |                                                 |                                                   |                         |
| Network        | Allows you to create rules on permitted         | Prevents unauthorized access, improves security,  | Weave Net               |
| policies       | connections and services. Requires a CNI        | segregates namespaces.                            | Calico                  |
|                | plugin.                                         |                                                   |                         |
|                |                                                 |                                                   |                         |
| Authorization  | Enables an API level integration into the       | Uses existing SSO to reduce the number of         | Requires custom work    |
| integration    | Kubernetes auth flow.                           | accounts and to centralize account                |                         |
|                |                                                 | management. Can integrate with almost any auth    |                         |
|                |                                                 | provider.                                         |                         |
|                |                                                 |                                                   |                         |
| Image          | Automates the scanning of vulnerabilities in    | Because CVEs always happen.                       | Docker                  |
| scanning       | your container images. Implemented at the       |                                                   | Snyk                    |
|                | CI stage of your pipeline.                      |                                                   | Twistlock               |
|                |                                                 |                                                   | Sonatype                |
|                |                                                 |                                                   | Aqua Security           |
|                |                                                 |                                                   |                         |
| Log            | Brings all the logs from your application into  | Logs are the best source of information on what   | Fluentd or ELK          |
| aggregation    | a one searchable place.                         | went wrong.                                       | stack are good bets     |
|                |                                                 |                                                   | for rolling your own.   |
