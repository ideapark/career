# OpenShift Project vs Kubernetes Namespace

## Namespace

A Kubernetes namespace provides a mechanism to scope resources in a cluster. In
OKD, a project is a Kubernetes namespace with additional annotations.

Namespaces provide a unique scope for:

  1. Named resources to avoid basic naming collisions.
  2. Delegated management authority to trusted users.
  3. The ability to limit community resource consumption.

Most objects in the system are scoped by namespace, but some are excepted and
have no namespace, including nodes and users.

## Project

A project is a Kubernetes namespace with additional annotations, and is the
central vehicle by which access to resources for regular users is managed. A
project allows a community of users to organize and manage their content in
isolation from other communities. Users must be given access to projects by
administrators, or if allowed to create projects, automatically have access to
their own projects.

Projects can have a separate name, displayName, and description.

  1. The mandatory name is a unique identifier for the project and is most
     visible when using the CLI tools or API. The maximum name length is 63
     characters.

  2. The optional displayName is how the project is displayed in the web console
     (defaults to name).

  3. The optional description can be a more detailed description of the project
     and is also visible in the web console.

Each project scopes its own set of:

| Project Owns     | Description                                                                          |
|------------------|--------------------------------------------------------------------------------------|
| Objects          | Pods, services, replication controllers, etc.                                        |
| Policies         | Rules for which users can or cannot perform actions on objects.                      |
| Constraints      | Quotas for each kind of object that can be limited.                                  |
| Service accounts | Service accounts act automatically with designated access to objects in the project. |

Cluster administrators can create projects and delegate administrative rights
for the project to any member of the user community. Cluster administrators can
also allow developers to create their own projects.
