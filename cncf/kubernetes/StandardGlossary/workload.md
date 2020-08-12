# Workload

- App Container

Application containers (or app containers) are the containers in a pod that are
started after any init containers have completed. An init container lets you
separate initialization details that are important for the overall workload, and
that don’t need to keep running once the application container has started. If a
pod doesn’t have any init containers configured, all the containers in that pod
are app containers.

- Container

A lightweight and portable executable image that contains software and all of
its dependencies. Containers decouple applications from underlying host
infrastructure to make deployment easier in different cloud or OS environments,
and for easier scaling.

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

- Job

A finite or batch task that runs to completion. Creates one or more Pod
Lifecycle objects and ensures that a specified number of them successfully
terminate. As Pods successfully complete, the Job tracks the successful
completions.

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

- Workload

A workload consists of a system of services or applications that can run to
fulfill a task or carry out a business process. Alongside the computer code that
runs to carry out the task, a workload also entails the infrastructure resources
that actually run that code.

For example, a workload that has a web element and a database element might run
the database in one StatefulSet of pods and the webserver via a Deployment that
consists of many web app pods, all alike.

The organisation running this workload may well have other workloads that
together provide a valuable outcome to its users.
