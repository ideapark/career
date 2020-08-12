# Quality of Service Classes

A node is overcommitted when it has a pod scheduled that makes no request, or
when the sum of limits across all pods on that node exceeds available machine
capacity.

In an overcommitted environment, it is possible that the pods on the node will
attempt to use more compute resource than is available at any given point in
time. When this occurs, the node must give priority to one pod over another. The
facility used to make this decision is referred to as a Quality of Service (QoS)
Class.

For each compute resource, a container is divided into one of three QoS classes
with decreasing order of priority:

| Priority    | Class Name | Description                                                                                                                                         |
| ----------- | ---------- | --------------------------------------------------------------------------------------------------------------------------------------------------- |
| 1 (highest) | Guaranteed | If limits and optionally requests are set (not equal to 0) for all resources and they are equal, then the container is classified as Guaranteed     |
| 2           | Burstable  | If requests and optionally limits are set (not equal to 0) for all resources, and they are not equal, then the container is classified as Burstable |
| 3 (lowest)  | BestEffort | If requests and limits are not set for any of the resources, then the container is classified as BestEffort                                         |

Memory is an incompressible resource, so in low memory situations, containers
that have the lowest priority are terminated first:

- Guaranteed containers are considered top priority, and are guaranteed to only
  be terminated if they exceed their limits, or if the system is under memory
  pressure and there are no lower priority containers that can be evicted.

- Burstable containers under system memory pressure are more likely to be
  terminated once they exceed their requests and not other BestEffort containers
  exist.

- BestEffort containers are treated with the lowest priority. Processes in these
  containers are first to be terminated if the system runs out of memory.
