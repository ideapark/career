# oc adm diagnostics

  1. Verifies that the default registry and router are running and correctly configured.
  2. Checks ClusterRoleBindings and ClusterRoles for consistency with base policy.
  3. Check that all of the client configuration contexts are valid and can be connected to.
  4. Checks that SkyDNS is working properly and the pods have SDN connectivity.
  5. Validates master and node configuration on the host.
  6. Checks that nodes are running and available.
  7. Analyzes host logs for known errors.
  8. Checks that systemd units are configured as expected for the host.
