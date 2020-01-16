# Architecture

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
