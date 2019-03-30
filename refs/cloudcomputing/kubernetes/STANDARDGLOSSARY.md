# Kubernetes Standardized Glossary

## Architecture

- Aggregation Layer

The aggregation layer lets you install additional Kubernetes-style APIs in your
cluster. When you've configured the Kubernetes API Server to support additional
APIs, you can add APIService objects to "claim" a URL path in the Kubernetes
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

- Controller

A controll loop that watches the shared state of the cluster through the
apiserver and makes changes attempting to move the current state towards the
desired state. Examples of controllers that ship with Kubernetes today are the
replication controller, endpoints controller, namespace controller, and
serviceaccounts controller.

- Ingress

An API object that manages external access to the services in a cluster,
typically HTTP. Ingress can provide load balancing, SSL termination and
name-based virtual hosting.

- Istio

An open platform (not Kubernetes-specific) that provides a uniform way to
integrate microservices, manage traffic flow, enforce policies, and aggregate
telemetry data. Adding Istio does not require changing application code. It is a
layer of infrastructure between a service and the network, which when combined
with service deployments, is commonly referred to as a service mesh. Istio's
control plane abstracts away the underlying cluster management platform, which
may be Kubernetes, Mesosphere, etc.

- Kubernetes API

The application that serves Kubernetes functionality through a RESTful interface
and stores the state of the cluster. Kubernetes resources and "records of
intent" are all stored as API objects, and modified via RESTful calls to the
API. The API allows configuration to be managed in a declarative way. Users can
interact with the Kubernetes API directly, or via tools like *kubectl*. The core
Kubernetes API is flexible and can be extended to support custom resources.

- Network Policy

A specification of how groups of Pods are allowed to communicate with each other
and with other network endpoints. Network Policies help you declaratively
configure which Pods are allowed to connect to each other, which namespaces are
allowed to communicate, and more specifically which port numbers to enforce each
policy on. NetworkPolicy resources use labels to select Pods and define rules
which specify what traffic is allowed to the selected Pods. Network Policies are
implemented by a supported network plugin provided by a network provider. Be
aware that creating a network resource without a controller to implement it will
have no effect.

- Resource Quotas

Provides constraints that limit aggregate resource consumption per Namespace.
Limits the quantity of objects that can be created in a namespace by type, as
well as the total amount of compute resources that may be consumed by resources
in that project.

- etcd

Consistent and highly-available key value store used as Kubernetes’ backing
store for all cluster data. Always have a backup plan for etcd’s data for your
Kubernetes cluster. For in-depth information on etcd, see etcd documentation.

- kube-apiserver

Component on the master that exposes the Kubernetes API. It is the front-end for
the Kubernetes control plane. It is designed to scale horizontally – that is, it
scales by deploying more instances. See Building High-Availability Clusters.

- kube-controller-manager

Component on the master that runs controllers. Logically, each controller is a
separate process, but to reduce complexity, they are all compiled into a single
binary and run in a single process.

- kube-scheduler

Component on the master that watches newly created pods that have no node
assigned, and selects a node for them to run on. Factors taken into account for
scheduling decisions include individual and collective resource requirements,
hardware/software/policy constraints, affinity and anti-affinity specifications,
data locality, inter-workload interference and deadlines.

## Community

- Approver

A person who can review and approve Kubernetes code contributions. While code
review is focused on code quality and correctness, approval is focused on the
holistic acceptance of a contribution. Holistic acceptance includes
backwards/forwards compatibility, adhering to API and flag conventions, subtle
performance and correctness issues, interactions with other parts of the system,
and others. Approver status is scoped to a part of the codebase. Approvers were
previously referred to as maintainers.

- CLA (Contributor License Agreement)

Terms under which a contributor grants a license to an open source project for
their contributions. CLAs help resolve legal disputes involving contributed
material and intellectual property (IP).

- Cloud Provider

Cloud provider is a company that offers cloud computing platform that can run
Kubernetes clusters. Cloud providers or sometime called Cloud Service Provider
(CSPs) provides cloud computing platforms. They may offer services such as
Infrastructure as a Service (IaaS) or Platform as a Service (PaaS). Cloud
providers host the Kubernetes cluster and also provide services that interact
with the cluster, such as Load Balancers, Storage Classes etc.

- Code Contributor

A person who develops and contributes code to the Kubernetes open source
codebase. They are also an active community member who participates in one or
more Special Interest Groups (SIGs) .

- Contributor

Someone who donates code, documentation, or their time to help the Kubernetes
project or community. Contributions include pull requests (PRs), issues,
feedback, special interest groups (SIG) participation, or organizing community
events.

- Developer (disambiguation)

May refer to: Application Developer, Code Contributor, or Platform Developer.
This overloaded term may have different meanings depending on the context

- Downstream (disambiguation)

May refer to: code in the Kubernetes ecosystem that depends upon the core
Kubernetes codebase or a forked repo.

  1. In the Kubernetes Community: Conversations often use downstream to mean the
     ecosystem, code, or third-party tools that rely on the core Kubernetes
     codebase. For example, a new feature in Kubernetes may be adopted by
     applications downstream to improve their functionality.

  2. In GitHub or git: The convention is to refer to a forked repo as
     downstream, whereas the source repo is considered upstream.

- Member

A continuously active contributor in the K8s community. Members can have issues
and PRs assigned to them and participate in special interest groups (SIGs)
through GitHub teams. Pre-submit tests are automatically run for members’ PRs. A
member is expected to remain an active contributor to the community.

- Reviewer

A person who reviews code for quality and correctness on some part of the
project. Reviewers are knowledgeable about both the codebase and software
engineering principles. Reviewer status is scoped to a part of the codebase.

- SIG (special interest group)

Community members who collectively manage an ongoing piece or aspect of the
larger Kubernetes open source project. Members within a SIG have a shared
interest in advancing a specific area, such as architecture, API machinery, or
documentation. SIGs must follow the SIG Governance guidelines but can have their
own contribution policy and channels of communication.

For more information, see the kubernetes/community repo and the current list of
SIGs and Working Groups.

- Upstream (disambiguation)

May refer to: core Kubernetes or the source repo from which a repo was forked.

  1. In the Kubernetes Community: Conversations often use upstream to mean the
     core Kubernetes codebase, which the general ecosystem, other code, or
     third-party tools relies upon. For example, community members may suggest
     that a feature is moved upstream so that it is in the core codebase instead
     of in a plugin or third-party tool.

  2. In GitHub or git: The convention is to refer to a source repo as upstream,
     whereas the forked repo is considered downstream.

- WG (working group)

Facilitates the discussion and/or implementation of a short-lived, narrow, or
decoupled project for a committee, SIG , or cross-SIG effort. Working groups are
a way of organizing people to accomplish a discrete task, and are relatively
easy to create and deprecate when inactive.

For more information, see the kubernetes/community repo and the current list of
SIGs and working groups.

## Core Object

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

- ConfigMap

An API object used to store non-confidential data in key-value pairs. Can be
consumed as environment variables, command-line arguments, or config files in a
volume. Allows you to decouple environment-specific configuration from your
container images , so that your applications are easily portable. When storing
confidential data use a Secret.

- CronJob

Manages a Job that runs on a periodic schedule. Similar to a line in a crontab
file, a CronJob object specifies a schedule using the cron format.

- DaemonSet

Ensures a copy of a Pod is running across a set of nodes in a cluster. Used to
deploy system daemons such as log collectors and monitoring agents that
typically must run on every Node.

- Deployment

An API object that manages a replicated application. Each replica is represented
by a Pod Lifecycle , and the Pods are distributed among the nodes of a cluster.

- Dynamic Volume Provision

Allows users to request automatic creation of storage Volumes. Dynamic
provisioning eliminates the need for cluster administrators to pre-provision
storage. Instead, it automatically provisions storage by user request. Dynamic
volume provisioning is based on an API object, StorageClass, referring to a
Volume Plugin that provisions a Volume and the set of parameters to pass to the
Volume Plugin.

- Job

A finite or batch task that runs to completion. Creates one or more Pod
Lifecycle objects and ensures that a specified number of them successfully
terminate. As Pods successfully complete, the Job tracks the successful
completions.

- Kubelet

An agent that runs on each node in the cluster. It makes sure that containers
are running in a pod. The kubelet takes a set of PodSpecs that are provided
through various mechanisms and ensures that the containers described in those
PodSpecs are running and healthy. The kubelet doesn’t manage containers which
were not created by Kubernetes.

- Persistent Volume

An API object that represents a piece of storage in the cluster. Available as a
general, pluggable resource that persists beyond the lifecycle of any individual
Pod. PersistentVolumes (PVs) provide an API that abstracts details of how
storage is provided from how it is consumed. PVs are used directly in scenarios
where storage can be created ahead of time (static provisioning). For scenarios
that require on-demand storage (dynamic provisioning), PersistentVolumeClaims
(PVCs) are used instead.

- Persistent Volume Claim

Claims storage resources defined in a PersistentVolume so that it can be mounted
as a volume in a container. Specifies the amount of storage, how the storage
will be accessed (read-only, read-write and/or exclusive) and how it is
reclaimed (retained, recycled or deleted). Details of the storage itself are in
the PersistentVolume specification.

- Pod

The smallest and simplest Kubernetes object. A Pod represents a set of running
containers on your cluster. A Pod is typically set up to run a single primary
container. It can also run optional sidecar containers that add supplementary
features like logging. Pods are commonly managed by a Deployment .

- Pod Security Policy

Enables fine-grained authorization of Pod Lifecycle creation and updates. A
cluster-level resource that controls security sensitive aspects of the Pod
specification. The PodSecurityPolicy objects define a set of conditions that a
Pod must run with in order to be accepted into the system, as well as defaults
for the related fields. Pod Security Policy control is implemented as an
optional admission controller.

- Quantity

A whole-number representation of small or large numbers using SI suffixes.
Quantities are representations of small or large numbers using a compact,
whole-number notation with SI suffixes. Fractional numbers are represented using
milli units, while large numbers can be represented using kilo, mega, or giga
units.

For instance, the number 1.5 is represented as 1500m, while the number 1000 can
be represented as 1k, and 1000000 as 1M. You can also specify binary-notation
suffixes; the number 2048 can be written as 2Ki.

The accepted decimal (power-of-10) units are m (milli), k (kilo, intentionally
lowercase), M (mega), G (giga), T (terra), P (peta), E (exa).

The accepted binary (power-of-2) units are Ki (kibi), Mi (mebi), Gi (gibi), Ti
(tebi), Pi (pebi), Ei (exbi).

- ReplicaSet

ReplicaSet is the next-generation Replication Controller. ReplicaSet, like
ReplicationController, ensures that a specified number of pods replicas are
running at one time. ReplicaSet supports the new set-based selector requirements
as described in the labels user guide, whereas a Replication Controller only
supports equality-based selector requirements.

- Replication Controller

Kubernetes service that ensures a specific number of instances of a pod are
always running. Will automatically add or remove running instances of a pod,
based on a set value for that pod. Allows the pod to return to the defined
number of instances if pods are deleted or if too many are started by mistake.

- Secret

Stores sensitive information, such as passwords, OAuth tokens, and ssh keys.
Allows for more control over how sensitive information is used and reduces the
risk of accidental exposure, including encryption at rest. A Pod references the
secret as a file in a volume mount or by the kubelet pulling images for a pod.
Secrets are great for confidential data and ConfigMaps for non-confidential
data.

- Service

An API object that describes how to access applications, such as a set of Pods,
and can describe ports and load-balancers. The access point can be internal or
external to the cluster.

- Service Account

Provides an identity for processes that run in a Pod. When processes inside Pods
access the cluster, they are authenticated by the API server as a particular
service account, for example, default. When you create a Pod, if you do not
specify a service account, it is automatically assigned the default service
account in the same namespace Namespace.

- StatefulSet

Manages the deployment and scaling of a set of Pods , and provides guarantees
about the ordering and uniqueness of these Pods. Like a Deployment, a
StatefulSet manages Pods that are based on an identical container spec. Unlike a
Deployment, a StatefulSet maintains a sticky identity for each of their Pods.
These pods are created from the same spec, but are not interchangeable: each has
a persistent identifier that it maintains across any rescheduling.

A StatefulSet operates under the same pattern as any other Controller. You
define your desired state in a StatefulSet object, and the StatefulSet
controller makes any necessary updates to get there from the current state.

- Storage Class

A StorageClass provides a way for administrators to describe different available
storage types. StorageClasses can map to quality-of-service levels, backup
policies, or to arbitrary policies determined by cluster administrators. Each
StorageClass contains the fields provisioner, parameters, and reclaimPolicy,
which are used when a Persistent Volume belonging to the class needs to be
dynamically provisioned. Users can request a particular class using the name of
a StorageClass object.

- Taint

A key-value pair and an effect to prevent the scheduling of pods on nodes or
node groups. Taints and Tolerations work together to ensure that pods are not
scheduled onto inappropriate nodes. One or more taints are applied to a node;
this marks that the node should not accept any pods that do not tolerate the
taints.

- Toleration

A key-value pair and an effect to enable the scheduling of pods on nodes or node
groups that have a matching taints. Tolerations and Taints work together to
ensure that pods are not scheduled onto inappropriate nodes. One or more
tolerations are applied to a pod ; this marks that the pod is allowed (but not
required) to be scheduled on nodes or node groups with matching taints.

- Volume

A directory containing data, accessible to the containers in a pod. A Kubernetes
volume lives as long as the pod that encloses it. Consequently, a volume
outlives any containers that run within the pod , and data is preserved across
container restarts.

- Volume Plugin

A Volume Plugin enables integration of storage within a Pod. A Volume Plugin
lets you attach and mount storage volumes for use by a Pod. Volume plugins can
be in tree or out of tree. In tree plugins are part of the Kubernetes code
repository and follow its release cycle. Out of tree plugins are developed
independently.

- kube-proxy

kube-proxy is a network proxy that runs on each node in the cluster. kube-proxy
is responsible for request forwarding. kube-proxy allows TCP and UDP stream
forwarding or round robin TCP and UDP forwarding across a set of backend
functions.
