# Tool

- Helm Chart

A package of pre-configured Kubernetes resources that can be managed with the
Helm tool. Charts provide a reproducible way of creating and sharing Kubernetes
applications. A single chart can be used to deploy something simple, like a
memcached Pod, or something complex, like a full web app stack with HTTP
servers, databases, caches, and so on.

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

- Kubectl

A command line tool for communicating with a Kubernetes API server. You can use
kubectl to create, inspect, update, and delete Kubernetes objects.

- Minikube

A tool for running Kubernetes locally. Minikube runs a single-node cluster
inside a VM on your computer.

- rkt

A security-minded, standards-based container engine.[-] rkt is an application
container engine featuring a pod-native approach, a pluggable execution
environment, and a well-defined surface area. rkt allows users to apply
different configurations at both the pod and application level and each pod
executes directly in the classic Unix process model, in a self-contained,
isolated environment.

- sysctl

sysctl is a semi-standardized interface for reading or changing the attributes
of the running Unix kernel. On Unix-like systems, sysctl is both the name of the
tool that administrators use to view and modify these settings, and also the
system call that the tool uses.

Container runtimes and network plugins may rely on sysctl values being set a
certain way.
