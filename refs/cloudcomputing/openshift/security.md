# How containers are secured

## Linux namespaces

enable creating an abstraction of a particular global system resource to make it
appear as a separate instance to processes within a namespace. Consequently,
several containers can use the same resource simultaneously without creating a
conflict.

## SELinux

provides an additional layer of security to keep containers isolated from each
other and from the host. SELinux allows administrators to enforce mandatory
access controls (MAC) for every user, application, process, and file.

## CGroups (control groups)

limit, account for, and isolate the resource usage (CPU, memory, disk I/O,
network, etc.) of a collection of processes. CGroups are used to ensure that
containers on the same host are not impacted by each other.

## Secure computing mode (seccomp)

profiles can be associated with a container to restrict available system calls.

## RHEL Atomic Host

Deploying containers using RHEL Atomic Host reduces the attack surface by
minimizing the host environment and tuning it for containers.
