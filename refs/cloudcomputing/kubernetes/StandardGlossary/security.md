# Security

- Certificate

A cryptographically secure file used to validate access to the Kubernetes
cluster. Certificates enable applications within a Kubernetes cluster to access
the Kubernetes API securely. Certificates validate that clients are allowed to
access the API.

- RBAC (Role-Based Access Control)

Manages authorization decisions, allowing admins to dynamically configure access
policies through the Kubernetes API. RBAC utilizes roles, which contain
permission rules, and role bindings, which grant the permissions defined in a
role to a set of users.

- Secret

Stores sensitive information, such as passwords, OAuth tokens, and ssh keys.
Allows for more control over how sensitive information is used and reduces the
risk of accidental exposure, including encryption at rest. A Pod references the
secret as a file in a volume mount or by the kubelet pulling images for a pod.
Secrets are great for confidential data and ConfigMaps for non-confidential
data.

- Security Context

The securityContext field defines privilege and access control settings for a
Pod or Container, including the runtime UID and GID. The securityContext field
in a Pod Lifecycle (applying to all containers) or container is used to set the
user, groups, capabilities, privilege settings, and security policies
(SELinux/AppArmor/Seccomp) and more that container processes use.

- rkt

A security-minded, standards-based container engine. rkt is an application
container engine featuring a pod-native approach, a pluggable execution
environment, and a well-defined surface area. rkt allows users to apply
different configurations at both the pod and application level and each pod
executes directly in the classic Unix process model, in a self-contained,
isolated environment.
