# istioctl profile list

The following built-in configuration profiles are currently available:

1. default:

enables components according to the default settings of the IstioControlPlane
API (recommend for production deployments). You can display the default setting
by running the command istioctl profile dump.

2. demo:

configuration designed to showcase Istio functionality with modest resource
requirements. It is suitable to run the Bookinfo application and associated
tasks. This is the configuration that is installed with the quick start
instructions, but you can later customize the configuration to enable additional
features if you wish to explore more advanced tasks.

NOTE: This profile enables high levels of tracing and access logging so it is
not suitable for performance tests.

3. minimal:

the minimal set of components necessary to use Istio’s traffic management
features.

4. sds:

similar to the default profile, but also enables Istio’s SDS (secret discovery
service). This profile comes with additional authentication features enabled by
default (Strict Mutual TLS).

5. remote:

used for configuring remote clusters of a multicluster mesh with a shared
control plane configuration.

The components marked as *Y* are installed within each profile:

|                        | default | demo | minimal | sds | remote |
|------------------------|---------|------|---------|-----|--------|
| [CORE COMPONENTS]      |         |      |         |     |        |
| istio-citadel          | Y       | Y    |         | Y   | Y      |
| istio-egressgateway    |         | Y    |         |     |        |
| istio-galley           | Y       | Y    |         | Y   |        |
| istio-ingressgateway   | Y       | Y    |         | Y   |        |
| istio-nodeagent        |         |      |         | Y   |        |
| istio-polit            | Y       | Y    | Y       | Y   |        |
| istio-policy           | Y       | Y    |         | Y   |        |
| istio-sidecar-injector | Y       | Y    |         | Y   | Y      |
| istio-telemetry        | Y       | Y    |         | Y   |        |
| [ADDONS]               |         |      |         |     |        |
| grafana                |         | Y    |         |     |        |
| istio-tracing          |         | Y    |         |     |        |
| kiali                  |         | Y    |         |     |        |
| prometheus             | Y       | Y    |         | Y   |        |
