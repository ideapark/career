# oc adm diagnostics

  1. Verifies that the default registry and router are running and correctly configured.
  2. Checks ClusterRoleBindings and ClusterRoles for consistency with base policy.
  3. Check that all of the client configuration contexts are valid and can be connected to.
  4. Checks that SkyDNS is working properly and the pods have SDN connectivity.
  5. Validates master and node configuration on the host.
  6. Checks that nodes are running and available.
  7. Analyzes host logs for known errors.
  8. Checks that systemd units are configured as expected for the host.

| Diagnostic Name            | Purpose                                                                                                                                                                                                                                       |
| ---                        | ---                                                                                                                                                                                                                                           |
| AggregatedLogging          | Check the aggregated logging integration for proper configuration and operation.                                                                                                                                                              |
| AnalyzeLogs                | Check systemd service logs for problems. Does not require a configuration file to check against.                                                                                                                                              |
| ClusterRegistry            | Check that the cluster has a networking container image registry for builds and image streams.                                                                                                                                                |
| ClusterRoleBindings        | Check that the default cluster role bindings are present and contain the expected subjects according to base policy.                                                                                                                          |
| ClusterRoles               | Check that cluster roles are present and contain the expected permissions according to base policy.                                                                                                                                           |
| ClusterRouter              | Check for a working default router in the router.                                                                                                                                                                                             |
| ConfigContexts             | Check for that each context in the client configuration is complete and has connectivity to its API server.                                                                                                                                   |
| DiagnosticPod              | Creates a pod that runs diagnostics from a application standpoint, which checks that DNS within the pod is working as expected and the credentials for the default service account authenticate correctly to the master API.                  |
| EtcdWriteVolume            | Check the volume of writes against etcd for a time period and classify them by operation and key. This diagnostic only runs if specifically requested, because it does not run as quickly as other diagnostics and can increase load on etcd. |
| MasterConfigCheck          | Check this host's master configuration file for problems.                                                                                                                                                                                     |
| MasterNode                 | Check that the master running on this host is also running a node to verify that it is a member of the cluster SDN.                                                                                                                           |
| MetricsApiProxy            | Check that the integrated Heapster metrics can be reached via the cluster API proxy.                                                                                                                                                          |
| NetworkCheck               | Create diagnostic pods on multiple nodes to diagnose common network issues from an application or pod standpoint. Run this diagnostic when the master can schedule pods on nodes, but the pods have connection issues.                        |
| NodeConfigCheck            | Checks this host's node configuration file for problems.                                                                                                                                                                                      |
| NodeDefinitions            | Check that the nodes defined in the master API are ready and can schedule pods.                                                                                                                                                               |
| RouteCertificateValidation | Check all route certificates for those that might be rejected by extended validation.                                                                                                                                                         |
| ServiceExternalIPs         | Check for existing services that specify external IPs, which are disallowed according to master configuration.                                                                                                                                |
| UnitStatus                 | Check systemd status for units on this host related to OKD. Does not require a configuration file to check against.                                                                                                                           |
