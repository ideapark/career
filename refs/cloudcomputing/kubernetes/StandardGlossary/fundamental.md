# Fundamental

- Annotation

A key-value pair that is used to attach arbitrary non-identifying metadata to
objects. The metadata in an annotation can be small or large, structured or
unstructured, and can include characters not permitted by labels. Clients such
as tools and libraries can retrieve this metadata.

- Cluster

A set of machines, called nodes, that run containerized applications managed by
Kubernetes. A cluster has several worker nodes and at least one master node.

- Container

A lightweight and portable executable image that contains software and all of
its dependencies. Containers decouple applications from underlying host
infrastructure to make deployment easier in different cloud or OS environments,
and for easier scaling.

- Container Environment Variables

Container environment variables are name=value pairs that provide useful
information into containers running in a Pod. Container environment variables
provide information that is required by the running containerized applications
along with information about important resources to the Containers . For
example, file system details, information about the container itself, and other
cluster resources such as service endpoints.

- Container runtime interface (CRI)

The container runtime interface (CRI) is an API for container runtimes to
integrate with kubelet on a node. For more information, see the CRI API and
specifications.

- Controller

A control loop that watches the shared state of the cluster through the
apiserver and makes changes attempting to move the current state towards the
desired state. Examples of controllers that ship with Kubernetes today are the
replication controller, endpoints controller, namespace controller, and
serviceaccounts controller.

- CustomResourceDefinition

Custom code that defines a resource to add to your Kubernetes API server without
building a complete custom server. Custom Resource Definitions let you extend
the Kubernetes API for your environment if the publicly supported API resources
can’t meet your needs.

- DaemonSet

Ensures a copy of a Pod is running across a set of nodes in a cluster. Used to
deploy system daemons such as log collectors and monitoring agents that
typically must run on every Node.

- Deployment

An API object that manages a replicated application. Each replica is represented
by a Pod Lifecycle, and the Pods are distributed among the nodes of a cluster.

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

- Image

Stored instance of a container that holds a set of software needed to run an
application. A way of packaging software that allows it to be stored in a
container registry, pulled to a local system, and run as an application. Meta
data is included in the image that can indicate what executable to run, who
built it, and other information.

- Init Container

One or more initialization containers that must run to completion before any app
containers run. Initialization (init) containers are like regular app
containers, with one difference: init containers must run to completion before
any app containers can start. Init containers run in series: each init container
must run to completion before the next init container begins.

- Job

A finite or batch task that runs to completion. Creates one or more Pod
Lifecycle objects and ensures that a specified number of them successfully
terminate. As Pods successfully complete, the Job tracks the successful
completions.

- Kubectl

A command line tool for communicating with a Kubernetes API server. You can use
kubectl to create, inspect, update, and delete Kubernetes objects.

- Kubelet

An agent that runs on each node in the cluster. It makes sure that containers
are running in a pod. The kubelet takes a set of PodSpecs that are provided
through various mechanisms and ensures that the containers described in those
PodSpecs are running and healthy. The kubelet doesn’t manage containers which
were not created by Kubernetes.

- Kubernetes API

The application that serves Kubernetes functionality through a RESTful interface
and stores the state of the cluster. Kubernetes resources and “records of
intent” are all stored as API objects, and modified via RESTful calls to the
API. The API allows configuration to be managed in a declarative way. Users can
interact with the Kubernetes API directly, or via tools like kubectl. The core
Kubernetes API is flexible and can also be extended to support custom resources.

- Label

Tags objects with identifying attributes that are meaningful and relevant to
users. Labels are key/value pairs that are attached to objects such as Pods.
They are used to organize and to select subsets of objects.

- Minikube

A tool for running Kubernetes locally. Minikube runs a single-node cluster
inside a VM on your computer.

- Name

A client-provided string that refers to an object in a resource URL, such as
/api/v1/pods/some-name. Only one object of a given kind can have a given name at
a time. However, if you delete the object, you can make a new object with the
same name.

- Namespace

An abstraction used by Kubernetes to support multiple virtual clusters on the
same physical cluster. Namespaces are used to organize objects in a cluster and
provide a way to divide cluster resources. Names of resources need to be unique
within a namespace, but not across namespaces.

- Node

A node is a worker machine in Kubernetes. A worker machine may be a VM or
physical machine, depending on the cluster. It has the Services necessary to run
Pods and is managed by the master components. The Services on a node include
Docker, kubelet and kube-proxy.

- Pod

The smallest and simplest Kubernetes object. A Pod represents a set of running
containers on your cluster. A Pod is typically set up to run a single primary
container. It can also run optional sidecar containers that add supplementary
features like logging. Pods are commonly managed by a Deployment .

- Pod Lifecycle

A high-level summary of what phase the Pod is in within its lifecyle. The Pod
Lifecycle is a high level summary of where a Pod is in its lifecyle. A Pod’s
status field is a PodStatus object, which has a phase field that displays one of
the following phases: Running, Pending, Succeeded, Failed, Unknown, Completed,
or CrashLoopBackOff.

- Pod Security Policy

Enables fine-grained authorization of Pod Lifecycle creation and updates. A
cluster-level resource that controls security sensitive aspects of the Pod
specification. The PodSecurityPolicy objects define a set of conditions that a
Pod must run with in order to be accepted into the system, as well as defaults
for the related fields. Pod Security Policy control is implemented as an
optional admission controller.

- RBAC (Role-Based Access Control)

Manages authorization decisions, allowing admins to dynamically configure access
policies through the Kubernetes API. RBAC utilizes roles, which contain
permission rules, and role bindings, which grant the permissions defined in a
role to a set of users.

- ReplicaSet

ReplicaSet is the next-generation Replication Controller. ReplicaSet, like
ReplicationController, ensures that a specified number of pods replicas are
running at one time. ReplicaSet supports the new set-based selector requirements
as described in the labels user guide, whereas a Replication Controller only
supports equality-based selector requirements.

- Resource Quotas

Provides constraints that limit aggregate resource consumption per Namespace.
Limits the quantity of objects that can be created in a namespace by type, as
well as the total amount of compute resources that may be consumed by resources
in that project.

- Selector

Allows users to filter a list of resources based on labels. Selectors are
applied when querying lists of resources to filter them by Labels.

- Service

An API object that describes how to access applications, such as a set of Pods ,
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

- UID

A Kubernetes systems-generated string to uniquely identify objects. Every object
created over the whole lifetime of a Kubernetes cluster has a distinct UID. It
is intended to distinguish between historical occurrences of similar entities.

- Volume

A directory containing data, accessible to the containers in a pod. A Kubernetes
volume lives as long as the pod that encloses it. Consequently, a volume
outlives any containers that run within the pod , and data is preserved across
container restarts.

- docker

Docker is a software technology providing operating-system-level virtualization
also known as containers. Docker uses the resource isolation features of the
Linux kernel such as cgroups and kernel namespaces, and a union-capable file
system such as OverlayFS and others to allow independent “containers” to run
within a single Linux instance, avoiding the overhead of starting and
maintaining virtual machines (VMs).

- kube-apiserver

Component on the master that exposes the Kubernetes API. It is the front-end for
the Kubernetes control plane. It is designed to scale horizontally – that is, it
scales by deploying more instances. See Building High-Availability Clusters.

- kube-controller-manager

Component on the master that runs controllers. Logically, each controller is a
separate process, but to reduce complexity, they are all compiled into a single
binary and run in a single process.

- kube-proxy

kube-proxy is a network proxy that runs on each node in the cluster. kube-proxy
is responsible for request forwarding. kube-proxy allows TCP and UDP stream
forwarding or round robin TCP and UDP forwarding across a set of backend
functions.
