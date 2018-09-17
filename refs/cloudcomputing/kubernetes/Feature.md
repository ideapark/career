# Kubernetes Features

## Automatic binpacking

Automatically places containers based on their resource requirements and other
constraints, while not sacrificing availability. Mix critical and best-effort
workloads in order to drive up utilization and save even more sources.

## Horizontal scaling

Scale your application up and down with a simple command, with a UI, or
automatically based on CPU usage.

## Automated rollouts and rollbacks

Kubernetes progressively roll out changes to your application or its
configuration, while monitoring application health to ensure it doesn't kill all
your instances at the same time. If something goes wrong, Kubernetes will
rollback the change for you. Take advantage of a growing ecosystem of deployment
solutions.

## Storage orchestration

Automatically mount the storage system of your choice, whether from local
storage, a public cloud provider such as GCP or AWS, or a network storage system
such as NFS, iSCSI, Gluster, Ceph, Cinder, or Flocker.

## Self-healing

Restarts containers that fail, replaces and reschedules containers when nodes
die, kill containers that don't respond to your user-defined health check, and
doesn't advertise them to clients until they are ready to serve.

## Service discovery and load balancing

No need to modify your application to use an unfamiliar service discovery
mechanism. Kubernetes gives containers their own IP addresses and a single DNS
name for a set of containers, and can load-balance across them.

## Secret and configuration management

Deploy and update secrets and application configuration without rebuilding your
image and without exposing secrets in your stack configuration.

## Batch execution

In addition to services, Kubernetes can manage your batch and CI workloads,
replacing containers that fail, if desired.
