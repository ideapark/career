# Resource Quota

## Quota Scopes

| Scope          | Description                                                                   |
| ---            | ---                                                                           |
| Terminating    | Match pods where spec.activeDeadlineSeconds >= 0                              |
| NotTerminating | Match pods where spec.activeDeadlineSeconds is nil                            |
| BestEffort     | Match pods that have best effort quality of service for either cpu or memory  |
| NotBestEffort  | Match pods that do not have best effort quality of service for cpu and memory |

A BestEffort scope restricts a quota to limiting the following resources:

- pods

A Terminating, NotTerminating, and NotBestEffort scope restricts a quota
tracking the following resources:

- pods
- memory
- request.memory
- limits.memory
- cpu
- requests.cpu
- limits.cpu
- ephemeral-storage
- requests.ephemeral-storage
- limits.ephemeral-storage

## LimitRange

A limit range, defined by a LimitRange object, enumerates compute resource
constraints in a project at the pod, container, image, image stream, and
persistent volume claim level, and specifies the amount of resources that a pod,
container, image, image stream, or persistent volume claim can consume.
