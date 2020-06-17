# Well-Known Labels, Annotations and Taints

Kubernetes reserves all labels and annotations in the *kubernetes.io* namespace.

## kubernetes.io/arch
Example: kubernetes.io/arch=amd64

Used on: Node

Kubelet populates this with runtime.GOARCH as defined by Go. This can be handy
if you are mixing arm and x86 nodes, for example.

## kubernetes.io/os
Example: kubernetes.io/os=linux

Used on: Node

Kubelet populates this with runtime.GOOS as defined by Go. This can be handy if
you are mixing operating systems in your cluster (e.g., mixing Linux and Windows
nodes).

## beta.kubernetes.io/arch (deprecated)
This label has been deprecated. Please use kubernetes.io/arch instead.

beta.kubernetes.io/os (deprecated)

This label has been deprecated. Please use kubernetes.io/os instead.

## kubernetes.io/hostname
Example: kubernetes.io/hostname=ip-172-20-114-199.ec2.internal

Used on: Node

Kubelet populates this with the hostname. Note that the hostname can be changed
from the “actual” hostname by passing the --hostname-override flag to kubelet.

## beta.kubernetes.io/instance-type
Example: beta.kubernetes.io/instance-type=m3.medium

Used on: Node

Kubelet populates this with the instance type as defined by the cloudprovider.
It will not be set if not using a cloudprovider. This can be handy if you want
to target certain workloads to certain instance types, but typically you want to
rely on the Kubernetes scheduler to perform resource-based scheduling, and you
should aim to schedule based on properties rather than on instance types (e.g.
require a GPU, instead of requiring a g2.2xlarge)

## failure-domain.beta.kubernetes.io/region (deprecated)

See failure-domain.beta.kubernetes.io/zone.

## failure-domain.beta.kubernetes.io/zone (deprecated)

Example:
failure-domain.beta.kubernetes.io/region=us-east-1
failure-domain.beta.kubernetes.io/zone=us-east-1c

Used on: Node, PersistentVolume

## topology.kubernetes.io/region

## topology.kubernetes.io/zone
