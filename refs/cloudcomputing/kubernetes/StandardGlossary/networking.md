# Networking

- Container network interface (CNI)

Container network interface (CNI) plugins are a type of Network plugin that
adheres to the appc/CNI specification.

  1. For information on Kubernetes and CNI refer to this.
  2. For information on Kubernetes and CNI, see “Network plugins”.

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
