# Storage

- Container Storage Interface (CSI)

The Container Storage Interface (CSI) defines a standard interface to expose
storage systems to containers. CSI allows vendors to create custom storage
plugins for Kubernetes without adding them to the Kubernetes repository
(out-of-tree plugins). To use a CSI driver from a storage provider, you must
first deploy it to your cluster. You will then be able to create a Storage Class
that uses that CSI driver.

- Dynamic Volume Provisioning

Allows users to request automatic creation of storage Volumes. Dynamic
provisioning eliminates the need for cluster administrators to pre-provision
storage. Instead, it automatically provisions storage by user request. Dynamic
volume provisioning is based on an API object, StorageClass, referring to a
Volume Plugin that provisions a Volume and the set of parameters to pass to the
Volume Plugin.

- Flexvolume

Flexvolume is an interface for creating out-of-tree volume plugins. The
Container Storage Interface is a newer interface which addresses several
problems with Flexvolumes. Flexvolumes enable users to write their own drivers
and add support for their volumes in Kubernetes. FlexVolume driver binaries and
dependencies must be installed on host machines. This requires root access. The
Storage SIG suggests implementing a CSI driver if possible since it addresses
the limitations with Flexvolumes.

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

- StatefulSet

Manages the deployment and scaling of a set of Pods, and provides guarantees
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

- Volume Plugin

A Volume Plugin enables integration of storage within a Pod. A Volume Plugin
lets you attach and mount storage volumes for use by a Pod. Volume plugins can
be in tree or out of tree. In tree plugins are part of the Kubernetes code
repository and follow its release cycle. Out of tree plugins are developed
independently.

- etcd

Consistent and highly-available key value store used as Kubernetes’ backing
store for all cluster data. Always have a backup plan for etcd’s data for your
Kubernetes cluster. For in-depth information on etcd, see etcd documentation.
