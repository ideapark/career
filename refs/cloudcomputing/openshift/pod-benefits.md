# Pod benefits

Kubernetes pods are a group of containers that act like a single VM: they have a
single IP address, they can share a file system, and they typically have similar
security settings. Grouping containers together vastly increases the number of
applications that can be brought to OpenShift. Rather than focusing on a
microservice model to the exclusion of all other patterns, pods enable
developers to port existing applications that need to share local resources
while still benefiting from a container-based model.

Pods are immutable, changes cannot be made to a pod definition while it is
running. OKD implements changes by terminating an existing pod and recreating it
with modified configuration, base image(s), or both. Pods are also treated as
expendable, and do not maintain state when recreated. Therefore pods should
usually be managed by higher-level controllers, rather than directly by users.
