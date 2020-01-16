# Operation

- Aggregation Layer

The aggregation layer lets you install additional Kubernetes-style APIs in your
cluster. When you’ve configured the Kubernetes API Server to support additional
APIs, you can add APIService objects to “claim” a URL path in the Kubernetes
API.

- Cloud Controller Manager

Cloud Controller Manager is an alpha feature in 1.8. In upcoming releases it
will be the preferred way to integrate Kubernetes with any cloud. Kubernetes
v1.6 contains a new binary called cloud-controller-manager.
cloud-controller-manager is a daemon that embeds cloud-specific control loops.
These cloud-specific control loops were originally in the
kube-controller-manager. Since cloud providers develop and release at a
different pace compared to the Kubernetes project, abstracting the
provider-specific code to the cloud-controller-manager binary allows cloud
vendors to evolve independently from the core Kubernetes code.

- Cluster

A set of machines, called nodes, that run containerized applications managed by
Kubernetes. A cluster has several worker nodes and at least one master node.

- CustomResourceDefinition

Custom code that defines a resource to add to your Kubernetes API server without
building a complete custom server. Custom Resource Definitions let you extend
the Kubernetes API for your environment if the publicly supported API resources
can’t meet your needs.

- Horizontal Pod Autoscaler

An API resource that automatically scales the number of pod replicas based on
targeted CPU utilization or custom metric targets. HPA is typically used with
Replication Controllers, Deployments, or Replica Sets. It cannot be applied to
objects that cannot be scaled, for example DaemonSets .

- HostAliases

A HostAliases is a mapping between the IP address and hostname to be injected
into a Pod’s hosts file. HostAliases is an optional list of hostnames and IP
addresses that will be injected into the Pod’s hosts file if specified. This is
only valid for non-hostNetwork Pods.

- Kops

A CLI tool that helps you create, destroy, upgrade and maintain
production-grade, highly available, Kubernetes clusters. NOTE: Officially
supports AWS only, with GCE and VMware vSphere in alpha.

kops provisions your cluster with:

  1. Fully automated installation
  2. DNS-based cluster identification
  3. Self-healing: everything runs in Auto-Scaling Groups
  4. Limited OS support (Debian preferred, Ubuntu 16.04 supported, early support for CentOS & RHEL)
  5. High availability (HA) support
  6. The ability to directly provision, or generate terraform manifests

You can also build your own cluster using Kubeadm as a building block. kops
builds on the kubeadm work.

- Kubeadm

A tool for quickly installing Kubernetes and setting up a secure cluster. You
can use kubeadm to install both the control plane and the worker node
components.

- Pod Disruption Budget

Also known as: PDB A Pod Disruption Budget allows an application owner to create
an object for a replicated application, that ensures a certain number or
percentage of Pods with an assigned label will not be voluntarily evicted at any
point in time. PDBs cannot prevent an involuntary disruption, but will count
against the budget. A Pod Disruption Budget allows an application owner to
create an object for a replicated application, that ensures a certain number or
percentage of Pods with an assigned label will not be voluntarily evicted at any
point in time. PDBs cannot prevent an involuntary disruption, but will count
against the budget.

- Pod Priority

Pod Priority indicates the importance of a Pod relative to other Pods. Pod
Priority gives the ability to set scheduling priority of a Pod to be higher and
lower than other Pods — an important feature for production clusters workload.

- PodPreset

An API object that injects information such as secrets, volume mounts, and
environment variables into pods at creation time. This object chooses the pods
to inject information into using standard selectors. This allows the podspec
definitions to be nonspecific, decoupling the podspec from environment specific
configuration.

- Preemption

Preemption logic in Kubernetes helps a pending Pod to find a suitable Node by
evicting low priority Pods existing on that Node. If a Pod cannot be scheduled,
the scheduler tries to preempt lower priority Pods to make scheduling of the
pending Pod possible.

- Resource Quotas

Provides constraints that limit aggregate resource consumption per Namespace.
Limits the quantity of objects that can be created in a namespace by type, as
well as the total amount of compute resources that may be consumed by resources
in that project.
