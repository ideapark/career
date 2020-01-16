# Extension

- Aggregation Layer

The aggregation layer lets you install additional Kubernetes-style APIs in your
cluster. When you’ve configured the Kubernetes API Server to support additional
APIs, you can add APIService objects to “claim” a URL path in the Kubernetes
API.

- Container Lifecycle Hooks

The lifecycle hooks expose events in the Container management lifecycle and let
the user run code when the events occur. Two hooks are exposed to Containers:
PostStart which executes immediately after a container is created and PreStop
which is blocking and is called immediately before a container is terminated.

- CustomResourceDefinition

Custom code that defines a resource to add to your Kubernetes API server without
building a complete custom server. Custom Resource Definitions let you extend
the Kubernetes API for your environment if the publicly supported API resources
can’t meet your needs.

- Device Plugin

Device Plugins are containers running in Kubernetes that provide access to a
vendor specific resource. Device Plugin are containers running in Kubernetes
that provide access to a vendor specific resource. Device Plugins advertise
these resources to kubelet and can be deployed manually or as a DeamonSet,
rather than writing custom Kubernetes code.

- Extensions

Extensions are software components that extend and deeply integrate with
Kubernetes to support new types of hardware. Most cluster administrators will
use a hosted or distribution instance of Kubernetes. As a result, most
Kubernetes users will need to install extensions and fewer will need to author
new ones.

- Ingress

An API object that manages external access to the services in a cluster,
typically HTTP. Ingress can provide load balancing, SSL termination and
name-based virtual hosting.

- Istio

An open platform (not Kubernetes-specific) that provides a uniform way to
integrate microservices, manage traffic flow, enforce policies, and aggregate
telemetry data. Adding Istio does not require changing application code. It is a
layer of infrastructure between a service and the network, which when combined
with service deployments, is commonly referred to as a service mesh. Istio’s
control plane abstracts away the underlying cluster management platform, which
may be Kubernetes, Mesosphere, etc.

- Managed Service

A software offering maintained by a third-party provider. Some examples of
Managed Services are AWS EC2, Azure SQL Database, and GCP Pub/Sub, but they can
be any software offering that can be used by an application. Service Catalog
provides a way to list, provision, and bind with Managed Services offered by
Service Brokers .

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

- Service Broker

An endpoint for a set of Managed Services offered and maintained by a
third-party. Service Brokers implement the Open Service Broker API spec and
provide a standard interface for applications to use their Managed Services.
Service Catalog provides a way to list, provision, and bind with Managed
Services offered by Service Brokers.

- Service Catalog

An extension API that enables applications running in Kubernetes clusters to
easily use external managed software offerings, such as a datastore service
offered by a cloud provider. It provides a way to list, provision, and bind with
external Managed Services from Service Brokers without needing detailed
knowledge about how those services are created or managed.
