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
