# Generic Scheduler

- Filter the Nodes

The available nodes are filtered based on the constraints or requirements
specified. This is done by running each node through the list of filter
functions called predicates.

- Prioritize the Filtered List of Nodes

This is achieved by passing each node through a series of priority functions
that assign it a score between 0 - 10, with 0 indicating a bad fit and 10
indicating a good fit to host the pod. The scheduler configuration can also take
in a simple weight (positive numeric value) for each priority function. The node
score provided by each priority function is multiplied by the weight (default
weight for most priorities is 1) and then combined by adding scores for each
node provided by all the priorities. This weight attribute can be used by
administrators to give higher importance to some priorities.

- Select the Best Fit Node

The nodes are sorted based on their scores and the node with the highest score
is selected to host the pod. If multiple nodes have the same high score, then
one of them is selected at random.

# Advanced Scheduling

- Pod Affinity and Anti-affinity
- Node Affinity
- Node Selectors
- Taints and Tolerations
